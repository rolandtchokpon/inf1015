git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/rolandTCHOKPON/inf1015.git
git push -u origin main
git pull //Pour faire une mise à jour entre les elements du depot local et 
           du depot distant

//---------//

git checkout -b nom_branch  //Pour creer une nouvelle branch 1
git switch nom_branch  //Pour passer d'une branch à l'autre
git switch -c nom_branch // Meme role que 1
git branch -D nom_branch   //Pour forcer la suppression d'une branche sans 
                           misàj
git branch -d nom_branch   //Pour supprimer une branch avec une retriction 
                           de miseàj préalable 
