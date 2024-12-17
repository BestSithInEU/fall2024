#include "ConfigReader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

ConfigReader::ConfigReader(const std::string& config_path)
    : config_path_(config_path) {}

bool ConfigReader::readConfig() {
  try {
    // Open and read the JSON file
    std::ifstream config_file(config_path_);
    if (!config_file.is_open()) {
      std::cerr << "Failed to open config file: " << config_path_ << std::endl;
      return false;
    }

    // Parse JSON content
    nlohmann::json json_data;
    config_file >> json_data;

    // Parse game settings and piece configurations
    parseGameSettings(json_data["game_settings"]);
    parsePieceConfigs(json_data["pieces"]);

    // Parse portal configurations if they exist
    if (json_data.contains("portals")) {
      parsePortalConfigs(json_data["portals"]);
    }

    return true;
  } catch (const std::exception& e) {
    std::cerr << "Error parsing config file: " << e.what() << std::endl;
    return false;
  }
}

void ConfigReader::parseGameSettings(const nlohmann::json& json) {
  game_settings_.name = json["name"].get<std::string>();
  game_settings_.board_size = json["board_size"].get<int>();
  game_settings_.turn_limit = json["turn_limit"].get<int>();
}

void ConfigReader::parsePieceConfigs(const nlohmann::json& json) {
  piece_configs_.clear();

  for (const auto& piece : json) {
    PieceConfig config;
    config.type = piece["type"].get<std::string>();

    // Parse positions for both colors
    if (piece["positions"].contains("white")) {
      for (const auto& pos : piece["positions"]["white"]) {
        Position position;
        position.x = pos["x"].get<int>();
        position.y = pos["y"].get<int>();
        config.white_positions.push_back(position);
      }
    }

    if (piece["positions"].contains("black")) {
      for (const auto& pos : piece["positions"]["black"]) {
        Position position;
        position.x = pos["x"].get<int>();
        position.y = pos["y"].get<int>();
        config.black_positions.push_back(position);
      }
    }

    // Parse movement rules
    const auto& movement = piece["movement"];
    config.movement.forward = movement.value("forward", 0);
    config.movement.sideways = movement.value("sideways", 0);
    config.movement.diagonal = movement.value("diagonal", 0);
    config.movement.l_shape = movement.value("l_shape", false);
    config.movement.first_move_forward =
        movement.value("first_move_forward", 0);
    config.movement.diagonal_capture = movement.value("diagonal_capture", 0);

    config.count = piece["count"].get<int>();
    piece_configs_.push_back(config);
  }
}

void ConfigReader::parsePortalConfigs(const nlohmann::json& json) {
  portal_configs_.clear();

  for (const auto& portal : json) {
    PortalConfig config;

    // Parse portal ID
    config.id = portal["id"].get<std::string>();

    // Parse positions
    config.positions.entry.x = portal["positions"]["entry"]["x"].get<int>();
    config.positions.entry.y = portal["positions"]["entry"]["y"].get<int>();
    config.positions.exit.x = portal["positions"]["exit"]["x"].get<int>();
    config.positions.exit.y = portal["positions"]["exit"]["y"].get<int>();

    // Parse properties
    const auto& props = portal["properties"];
    config.properties.preserve_direction =
        props.value("preserve_direction", true);
    config.properties.allowed_colors =
        props["allowed_colors"].get<std::vector<std::string>>();
    config.properties.cooldown = props.value("cooldown", 0);

    portal_configs_.push_back(config);
  }
}

GameSettings ConfigReader::getGameSettings() const { return game_settings_; }

std::vector<PieceConfig> ConfigReader::getPieceConfigs() const {
  return piece_configs_;
}

std::vector<PortalConfig> ConfigReader::getPortalConfigs() const {
  return portal_configs_;
}
