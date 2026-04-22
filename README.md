# My Top - Unix Process Monitor

## 📊 Présentation du projet
**My Top** est une réimplémentation de la commande système `top` en langage **C**. 
L'objectif est de fournir un outil de monitoring en temps réel des processus et des ressources système (CPU, Mémoire, Swap) via une interface utilisateur textuelle (TUI).

Ce projet repose sur la lecture et le parsing des fichiers du système de fichiers virtuel `/proc` (procfs) et utilise la bibliothèque **ncurses** pour l'affichage dynamique.

> **Note :** Ce projet a été réalisé dans le cadre du module G-PSU-100 d'Epitech.

---

## ✨ Fonctionnalités

### 🖥️ Section Système (Header)
- **Uptime** : Temps écoulé depuis le démarrage du système.
- **Utilisateurs** : Nombre d'utilisateurs actuellement connectés.
- **Load Average** : Charge moyenne du système (1, 5 et 15 minutes).
- **Tasks** : État global des processus (total, running, sleeping, stopped, zombie).
- **CPU usage** : Détail de l'utilisation processeur (user, system, idle, etc.).
- **Memory & Swap** : Utilisation de la mémoire vive et de la partition d'échange avec unités cycliques.

### ⚙️ Section Processus
Affiche un tableau détaillé des processus incluant:
- **PID** (identifiant), **USER** (propriétaire), **PR** (priorité), **NI** (valeur nice).
- **VIRT**, **RES**, **SHR** (gestion mémoire).
- **S** (statut), **%CPU**, **%MEM**.
- **TIME+** (temps processeur cumulé) et **COMMAND**.

---

## 🚀 Installation et Lancement

### Prérequis
La bibliothèque **ncurses** doit être installée sur votre système.

### Compilation
Le projet inclut un `Makefile` complet :
```
make
```
### Exécution
Lancer le programme avec les options par défaut :
```
my_top
```
Options disponibles 
- -d <secondes> : Modifie l'intervalle de rafraîchissement (Défaut : 3.0s).
- -n <nombre> : Définit le nombre d'itérations avant de quitter automatiquement.

Exemple : ./my_top -d 1.5 -n 10

---

## 🛠️ Interactions clavier
Pendant l'exécution, vous pouvez utiliser les touches suivantes:
- E	-> Change l'unité de mesure de la mémoire (KiB, MiB, GiB, etc.).
- K	-> Ouvre une invite pour "tuer" (envoyer un signal) à un processus via son PID.
- Q	-> Quitte le programme immédiatement.

---

## 📁 Structure du projet
- `top_header/` : Gestion des statistiques globales du système.
- `top_columns/` : Extraction et formatage des données par processus.
- `lib/my/` : Fonctions utilitaires de base.
- `include/` : Définitions des structures et prototypes.
- `tests/` : Suite de tests unitaires utilisant Criterion

---

## 🧪 Tests
Pour lancer les tests unitaires et vérifier la couverture du code :
```
make test_run
```
