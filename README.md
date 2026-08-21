# ✈️ GestionBilletAvion2.0

Application desktop de gestion de réservations et de billets d'avion développée en **C++ avec Qt**.

Le projet permet de gérer les principales opérations liées aux vols, aux aéroports, aux clients, aux réservations et aux billets.

## 📋 Description

**GestionBilletAvion2.0** est une application desktop développée dans le cadre d'un projet universitaire.

L'objectif est de proposer une interface permettant de gérer les informations liées à une compagnie aérienne et aux réservations de billets.

L'application repose sur une architecture organisée autour de plusieurs couches, notamment :

* `models` : modèles représentant les données de l'application ;
* `dao` : accès et manipulation des données ;
* `database` : gestion de la connexion et de la base de données ;
* `ui` : interfaces graphiques de l'application.

## ⚙️ Fonctionnalités

L'application permet notamment de gérer :

* ✈️ Les vols
* 🛫 Les aéroports
* 👤 Les clients
* 🎫 Les billets
* 📅 Les réservations
* 💺 Les sièges
* 💰 Les prix des billets
* 🔄 Les différents statuts des réservations
* 🧳 Les types de voyage

Les données sont organisées autour de plusieurs entités telles que les clients, les réservations, les billets, les vols et les aéroports.

## 🛠️ Technologies utilisées

* **C++**
* **Qt 6**
* **Qt Widgets**
* **Qt Creator**
* **SQLite**
* **SQL**
* **Qt SQL**

## 🏗️ Architecture du projet

```text
version_final/
│
├── assets/
│
├── sql/
│   └── init.sql
│
├── src/
│   ├── dao/
│   ├── database/
│   ├── models/
│   ├── ui/
│   ├── DatabaseManager.cpp
│   └── main.cpp
│
├── build/
│
├── airline_booking.pro
├── main.cpp
├── mainwindow.h
├── resources.qrc
└── logo.png
```

## 🗄️ Base de données

La base de données contient notamment les tables :

* `AEROPORT`
* `VOL`
* `CLIENT`
* `RESERVATION`
* `BILLET`

Les relations entre les différentes entités permettent notamment d'associer :

* un vol à ses aéroports de départ et d'arrivée ;
* une réservation à un client ;
* un billet à une réservation ;
* un billet à un vol.

Une contrainte d'unicité est également utilisée pour empêcher l'attribution du même siège à plusieurs billets pour un même vol.

## 👥 Répartition du travail

Ce projet a été réalisé en collaboration.

### Antonio

**Antonio** a principalement réalisé la **conception et la mise en place de la base de données**, notamment :

* conception du modèle de données ;
* création des tables ;
* définition des clés primaires ;
* définition des clés étrangères ;
* définition des relations entre les différentes entités ;
* préparation des scripts SQL.

### Jeanel

**Jeanel** a principalement réalisé le **développement de l'application**, notamment :

* développement de l'interface graphique avec Qt ;
* implémentation de la logique de l'application ;
* développement des modèles ;
* développement des DAO ;
* gestion des interactions avec la base de données ;
* intégration des différentes parties de l'application ;
* développement et organisation des fonctionnalités de gestion.

## 🚀 Installation

### Prérequis

Pour compiler le projet, il est nécessaire d'avoir :

* Qt 6
* Qt Creator
* un compilateur C++ compatible
* SQLite

### Lancer le projet

1. Cloner le dépôt :

```bash
git clone https://github.com/nel-63/GestionBilletAvion2.0.git
```

2. Ouvrir le fichier suivant avec Qt Creator :

```text
version_final/airline_booking.pro
```

3. Sélectionner une version compatible de Qt.

4. Configurer le kit de compilation.

5. Compiler le projet.

6. Exécuter l'application.

## 🗃️ Initialisation de la base de données

Le script SQL permettant de créer la structure de la base de données se trouve dans :

```text
version_final/sql/init.sql
```

Un script SQL supplémentaire est également disponible à la racine du dépôt :

```text
base.sql
```

## 📚 Objectifs pédagogiques

Ce projet nous a permis de mettre en pratique plusieurs notions de développement logiciel :

* programmation orientée objet en C++ ;
* développement d'interfaces graphiques avec Qt ;
* conception de bases de données relationnelles ;
* langage SQL ;
* accès aux données ;
* architecture DAO ;
* séparation des responsabilités ;
* gestion des événements dans une interface graphique ;
* travail collaboratif avec Git et GitHub.

## 👨‍💻 Auteurs

**Jeanel Zazio**
Développement de l'application et intégration des différentes fonctionnalités.

**Antonio**
Conception et développement de la base de données.

---

## 📌 Projet universitaire

Projet réalisé dans le cadre de la formation en informatique.
