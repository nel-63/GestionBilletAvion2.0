create database if not exists GESTION_BILLET_AVION
character set	utf8mb4
collate utf8mb4_unicode_ci;

USE GESTION_BILLET_AVION;
/*****************************************************/
create table AEROPORT (
 id_aeroport INT unsigned not null auto_increment,
 code_iata varchar(3) not null,
 nom_ville varchar(100) not null,
 nom_pays varchar(100) not null,
 nom_aeroport varchar(100) not null,
 
 primary key (id_aeroport),
 unique key (code_iata)
 );
 
 /*****************************************************/
 create table VOL (
  id_vol INT  unsigned not null auto_increment,
  num_avion varchar (20) not null,
  
  -- clés étrangères vers aeroport
  id_depart_aeroport INT unsigned not null,
  id_arrivee_aeroport INT unsigned not null,
  
  date_depart date not null,
  heure_depart time not null,
  date_arrivee date not null,
  heure_arrivee time not null,
  
  -- pour l'intégrité référentielle
  foreign key (id_depart_aeroport) references aeroport(id_aeroport) on delete restrict,
  foreign key (id_arrivee_aeroport) references aeroport(id_aeroport) on delete restrict,
  
  primary key(id_vol)
  );

/*************************************/

create table BILLET (
 id_billet int unsigned not null auto_increment,
 id_reservation int unsigned not null,
 id_vol int unsigned not null,
 
 num_siège varchar(5) not null,
 classe ENUM('Economy', 'Business', 'First') NOT NULL,
 prix_billet decimal(10,2) not null,
 
 primary key (id_billet),
 foreign key (id_reservation) references reservation(id_reservation) on delete cascade,
 foreign key (id_vol) references vol(id_vol) on delete restrict,
 
 unique key	idx_unique_siege (id_vol,num_siège)
 );
 
/********************************/

create table reservation (
 id_reservation int unsigned auto_increment,
 id_client int unsigned not null,
 date_reservation datetime default current_timestamp,
 statut ENUM('En Attente', 'Confirmée', 'Annulée', 'Échouée') NOT NULL,
 montant_total decimal(10,2) not null,
 type_travel enum('aller_simple' , 'aller_retour' , 'multi_destination') not null,
 
 primary key(id_reservation),
 FOREIGN KEY (id_client) REFERENCES CLIENT(id_client) ON DELETE RESTRICT
 );
 
 /***********************************************/
 
 CREATE TABLE CLIENT (
    id_client INT UNSIGNED auto_increment,
    nom VARCHAR(100) NOT NULL,
    prenom VARCHAR(100) not null,
    email VARCHAR(255) UNIQUE default null,
    num_passeport VARCHAR(60) NULL, 
    contact varchar(60) unique default ("doesn't have"),
	mot_de_passe_hache CHAR(60) NOT NULL,
     
	primary key (id_client)
);
  
 
 
