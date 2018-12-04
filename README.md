# Utf-8 converter

Ce programme est destiné à la conversion des fichiers presents dans le dossier donné et ses sous dossiers.

## Utilisation

Vous ne pouvez utiliser ce programme que en mode console sous windows.
Pour cela, ouvrez une cmd dans le dossier "Converisseur" ([shift]+[clique droit] -> "ouvrir une fenetre de commande ici"), entrez `converter C:\chemin\vers\le\dossier\a\traiter\ C:\chemin\vers\le\dossier\final\`.
Puis suivez les indications à l'écran.

## Fonctionnement

Le programme va dans un premier temps recopier l'arborescence et créer les fichiers ".php" (seulement) rempli uniquement avec le BOM UTF-8 (`EF BB BF` en Hexadécimal) dans un premier temps pour spécifier explicitement l'encodage du fichier.
Ensuite, le programme va lire tous les caractères des fichiers de base uns à un et va insérer dans les fichiers de destination la valeur héxadécimale depuis une table de correspondance entre la valeur entière du caractère en C++ et son code héxa.
Puis, le programme va lire tous les fichiers nouvellement créés et va enlever les 3 premiers caractères (le BOM qui avait été mis lors de la création des fichiers).

Lors de ces opérations, le programme omet volontairement les fichiers déjà encodés en UTF-8, il leur appliquerait une conversion sur chaque octets (alors que l'UTF-8 comporte des caractères encodés sur deux octets).
Le programme omet également tous les fichiers non php, ceux-ci étant les plus critique pour l'encodage des données.
