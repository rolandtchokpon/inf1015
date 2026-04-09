# Répartition du travail

## Membre 1
Responsable du modèle de données lié aux pièces et à la gestion des rois.

### Fichiers
- `Position.hpp`
- `Piece.hpp`
- `Piece.cpp`
- `ExceptionRoi.hpp`
- `Roi.hpp`
- `Roi.cpp`

### Tâches
- Créer la structure `Position`.
- Créer la classe de base `Piece`.
- Gérer la position d’une pièce sur l’échiquier.
- Créer la classe `Roi` dérivée de `Piece`.
- Ajouter une variable de classe pour compter le nombre d’instances de `Roi`.
- Lancer une exception lorsqu’une tentative de création d’un troisième roi est faite.
- Vérifier que le compteur est correctement mis à jour à la destruction.

## Membre 2
Responsable du déplacement temporaire, de l’affichage et de l’intégration.

### Fichiers
- `DeplacementTemporaire.hpp`
- `DeplacementTemporaire.cpp`
- `Affichage.hpp`
- `Affichage.cpp`
- `main.cpp`

### Tâches
- Créer la classe `DeplacementTemporaire` en utilisant le principe RAII.
- Déplacer temporairement une pièce dans le constructeur.
- Remettre automatiquement la pièce à son ancienne position dans le destructeur.
- Créer les fonctions d’affichage dans un `namespace` distinct.
- Afficher le message d’erreur lors de la réception de l’exception.
- Intégrer les tests dans `main.cpp`.
- Vérifier que l’exécution continue correctement après la gestion de l’exception.

