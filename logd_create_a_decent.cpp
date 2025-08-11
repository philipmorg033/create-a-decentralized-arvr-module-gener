#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "json/json.h" // for parsing JSON data

using namespace std;

// Forward declarations
class ARVRModule;
class Blockchain;
class AssetManager;

// Data structures
struct ModuleConfig {
    string name;
    string description;
    vector<string> dependencies;
    string code;
};

struct ModuleInstance {
    string moduleId;
    string ownerId;
    string blockchainId;
};

// ARVRModule class
class ARVRModule {
public:
    string id;
    string name;
    string description;
    vector<string> dependencies;
    string code;

    ARVRModule(string _id, string _name, string _description, vector<string> _dependencies, string _code)
        : id(_id), name(_name), description(_description), dependencies(_dependencies), code(_code) {}
};

// Blockchain class
class Blockchain {
public:
    string id;
    string name;
    string blockchainType;

    Blockchain(string _id, string _name, string _blockchainType)
        : id(_id), name(_name), blockchainType(_blockchainType) {}
};

// AssetManager class
class AssetManager {
public:
    unordered_map<string, ARVRModule> modules;
    unordered_map<string, Blockchain> blockchains;
    unordered_map<string, ModuleInstance> instances;

    void addModule(ARVRModule module);
    void addBlockchain(Blockchain blockchain);
    void generateModuleInstance(ModuleConfig config);
};

int main() {
    AssetManager assetManager;

    // Sample data
    ARVRModule module("module1", "My AR Module", "A sample AR module", {"module2", "module3"}, "module_code");
    Blockchain blockchain("blockchain1", "Ethereum", "ethereum");

    assetManager.addModule(module);
    assetManager.addBlockchain(blockchain);

    ModuleConfig config = {"module1", "My AR Module Instance", {"module2", "module3"}, "instance_code"};
    assetManager.generateModuleInstance(config);

    return 0;
}

void AssetManager::addModule(ARVRModule module) {
    modules[module.id] = module;
}

void AssetManager::addBlockchain(Blockchain blockchain) {
    blockchains[blockchain.id] = blockchain;
}

void AssetManager::generateModuleInstance(ModuleConfig config) {
    ModuleInstance instance;
    instance.moduleId = config.name;
    instance.ownerId = "owner_id"; // Replace with actual owner ID
    instance.blockchainId = "blockchain1"; // Replace with actual blockchain ID
    instances[config.name] = instance;

    // Generate and store the instance code (e.g., in a database or file)
    string instanceCode = generateInstanceCode(config);
    cout << "Generated instance code: " << instanceCode << endl;
}

string generateInstanceCode(ModuleConfig config) {
    // Implement the logic to generate the instance code based on the module config
    // For demonstration purposes, return a simple JSON string
    Json::Value json;
    json["moduleId"] = config.name;
    json["ownerId"] = "owner_id"; // Replace with actual owner ID
    json["blockchainId"] = "blockchain1"; // Replace with actual blockchain ID
    json["code"] = config.code;

    Json::StreamWriterBuilder builder;
    return Json::writeString(builder, json);
}