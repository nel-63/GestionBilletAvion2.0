PRAGMA foreign_keys = ON;

CREATE TABLE IF NOT EXISTS users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    password TEXT NOT NULL,
    role TEXT NOT NULL
);

CREATE TABLE IF NOT EXISTS clients (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    nom TEXT NOT NULL,
    prenom TEXT NOT NULL,
    email TEXT,
    telephone TEXT
);

CREATE TABLE IF NOT EXISTS vols (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    code TEXT NOT NULL,
    destination TEXT NOT NULL,
    date TEXT NOT NULL,
    heure TEXT NOT NULL,
    compagnie TEXT,
    prix REAL DEFAULT 0
);

CREATE TABLE IF NOT EXISTS reservations (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    client_id INTEGER NOT NULL,
    vol_id INTEGER NOT NULL,
    date_reservation TEXT NOT NULL,
    statut TEXT NOT NULL,
    FOREIGN KEY (client_id) REFERENCES clients(id) ON DELETE CASCADE,
    FOREIGN KEY (vol_id) REFERENCES vols(id) ON DELETE CASCADE
);

INSERT OR IGNORE INTO users (username, password, role) VALUES ('admin', 'admin123', 'admin');
INSERT OR IGNORE INTO users (username, password, role) VALUES ('user', 'user123', 'user');

INSERT OR IGNORE INTO clients (nom, prenom, email, telephone) VALUES ('Dupont', 'Jean', 'jean.dupont@example.com', '+33123456789');
INSERT OR IGNORE INTO clients (nom, prenom, email, telephone) VALUES ('Martin', 'Claire', 'claire.martin@example.com', '+33788990011');

INSERT OR IGNORE INTO vols (code, destination, date, heure, compagnie, prix) VALUES ('AF123', 'Paris', '2025-11-01', '08:30:00', 'AirFrance', 150.0);
INSERT OR IGNORE INTO vols (code, destination, date, heure, compagnie, prix) VALUES ('BA456', 'Londres', '2025-11-02', '12:00:00', 'BritishAirways', 120.0);

INSERT OR IGNORE INTO reservations (client_id, vol_id, date_reservation, statut) VALUES (1, 1, '2025-09-30', 'Confirmée');