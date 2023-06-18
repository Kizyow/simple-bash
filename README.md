# Simple Bash (mbash)
## Réalisé par Rémy KINZELIN et Alexandre PERROT

L’objectif consiste à écrire une version miniature de bash, nommée mbash qui permet de lancer interactivement des commandes en utilisant exactement la même syntaxe que bash.
Ce projet a été réalisé dans le cadre de notre BUT Informatique

## Détails technique
mbash est vraiment une version extrêmement limitée par rapport à bash. Le minimum demandé consiste à pouvoir se déplacer avec la commande cd, à pouvoir afficher le répertoire courant avec pwd et à lancer
une commande, comme le fait bash, c’est-à-dire en respectant le contenu de la variable PATH. Il est également demandé de pouvoir disposer, du caractère & qui permet de lancer la commande en arrière plan.

Interdiction d'utiliser le véritable bash mais d'utiliser 'system' en C ou même 'execve'

## Mise en place d'un package Debian

Afin que notre programme mbash puisse être isntallé sur n'importe quel machine Linux, on doit mettre à disposition ce programme sur un serveur HTTP et d'en créer un package et de le signer avec les clés GPG
afin que l'utilisateur final le mette dans son /etc/apt/sources.list.d
