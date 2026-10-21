
#include <iostream>
#include <string>
#include "nlohmann/json.hpp"
#include "Agent.h"
#include <cpr/cpr.h>

using json = nlohmann::json;

const std::string instructions =
    "You are a repository analysis assistant. "
    "Help the user understand GitHub repositories, "
    "dependencies, and software issues. "
    "Do not invent repository files or claim to have "
    "inspected files unless their contents were provided.";

void createAgent(const std::string& repoUrl) {

    // Initialize conversation history once
    json messages = json::array({
        {
            {"role", "system"},
            {"content", instructions}
        },
        {
            {"role", "user"},
            {"content", "Repository URL: " + repoUrl}
        }
    });

    std::cout << "Agent initialized for: "
              << repoUrl << "\n";
    std::cout << "Type 'exit' to quit.\n";

    while (true) {

        std::string userInput;

        std::cout << "\nYou: ";

        // Wait for user input
        if (!std::getline(std::cin, userInput)) {
            break;
        }

        // Terminate the conversation
        if (userInput == "exit") {
            std::cout << "Agent: Session terminated.\n";
            break;
        }

        if (userInput.empty()) {
            continue;
        }

        // Add new user message to history
        messages.push_back({
            {"role", "user"},
            {"content", userInput}
        });

        json request = {
            {"model", "gemma4:e4b"},
            {"messages", messages},
            {"stream", false}
        };

        auto response = cpr::Post(
            cpr::Url{"http://localhost:11434/api/chat"},
            cpr::Header{
                {"Content-Type", "application/json"}
            },
            cpr::Body{request.dump()}
        );

        // Check HTTP response
        if (response.error.code != cpr::ErrorCode::OK ||
            response.status_code != 200) {

            std::cerr << "Request failed: "
                      << response.error.message
                      << " (HTTP " << response.status_code
                      << ")\n";

            // Remove failed user message
            messages.erase(messages.size() - 1);
            continue;
        }

        try {
            json result = json::parse(response.text);

            std::string agentReply =
                result.at("message")
                      .at("content")
                      .get<std::string>();

            std::cout << "\nAgent: "
                      << agentReply << "\n";

            // Save the assistant response
            messages.push_back({
                {"role", "assistant"},
                {"content", agentReply}
            });

        } catch (const std::exception& e) {
            std::cerr << "Response parsing failed: "
                      << e.what() << "\n";

            messages.erase(messages.size() - 1);
        }
    }
}

