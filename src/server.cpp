//
//  server.cpp
//  TP C++
//  Eric Lecolinet - Telecom ParisTech - 2016.
//

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "tcpserver.h"
#include "database.h"

const int PORT = 3331;

// Fonction utilitaire pour nettoyer les \n et \r des réponses
std::string cleanResponse(const std::string& response) {
  std::string clean = response;
  clean.erase(std::remove(clean.begin(), clean.end(), '\n'), clean.end());
  clean.erase(std::remove(clean.begin(), clean.end(), '\r'), clean.end());
  return clean;
}

int main(int argc, char* argv[])
{
  // Créer la base de données
  Database db;

  // Remplir avec quelques données pour tester
  db.createVideo("video1", "/path/to/video1.mp4", 120);
  db.createPhoto("photo1", "/path/to/photo1.jpg", 48.8566, 2.3522);
  db.createFilm("film1", "/path/to/film1.mkv", 180, new int[2]{60, 120}, 2);

  // Créer le serveur TCP
  auto* server =
  new TCPServer( [&](std::string const& request, std::string& response) {

    std::cout << "Request: " << request << std::endl;

    // Parser la requête
    std::istringstream iss(request);
    std::string command, arg;
    iss >> command >> arg;

    // Répondre selon la commande
    if (command == "search" && !arg.empty()) {
      std::ostringstream oss;
      std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
      db.search(arg);
      std::cout.rdbuf(old);
      response = cleanResponse(oss.str());
    }
    else if (command == "play" && !arg.empty()) {
      std::ostringstream oss;
      std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
      db.play(arg);
      std::cout.rdbuf(old);
      response = cleanResponse(oss.str());
    }
    else if (command == "list") {
      std::ostringstream oss;
      std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
      db.printAll();
      std::cout.rdbuf(old);
      response = cleanResponse(oss.str());
    }
    else if (command == "groups") {
      std::ostringstream oss;
      std::streambuf* old = std::cout.rdbuf(oss.rdbuf());
      db.printAllGroups();
      std::cout.rdbuf(old);
      response = cleanResponse(oss.str());
    }
    else {
      response = "ERREUR: Commande inconnue. Utilisez: search|play|list|groups";
    }

    if (response.empty()) {
      response = "OK";
    }

    return true;
  });

  // Lancer la boucle infinie du serveur
  std::cout << "Starting Server on port " << PORT << std::endl;

  int status = server->run(PORT);

  // En cas d'erreur
  if (status < 0) {
    std::cerr << "Could not start Server on port " << PORT << std::endl;
    return 1;
  }

  return 0;
}

