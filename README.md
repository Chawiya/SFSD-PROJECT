# Projet : POO_PROJECT
Application : Système de gestion d'une clinique médicale (console Java)

## Description
Personne : classe abstraite de base (id, nom, prénom, téléphone, date de naissance), calcul d’âge, afficherProfil() abstraite.
Patient : hérite de Personne, ajoute NSS, groupe sanguin, antécédents, avec ajouterAntecedent() et afficherDossier().
PersonnelMedical : hérite de Personne, ajoute matricule, date d’embauche, salaire.
Medecin et Infirmier : héritent de PersonnelMedical, ajoutent leurs champs métiers (spécialité/tarif et service/grade) et redéfinissent afficherProfil().
Consultation : relie patient + médecin avec date, diagnostic, notes, statut et ordonnance.
Ordonnance : liée à une consultation, contient une liste de Medicament, avec validation métier.
Medicament : nom, dosage, durée, contre-indications.
CliniqueMedicale : classe centrale qui gère les listes, ajouts, recherches, création consultation, disponibilité médecin, revenus du jour.
Main : menu interactif, saisie utilisateur, validations, affichages, et gestion d’exceptions.
Package exception : exceptions personnalisées (PatientInexistant, MedecinIndisponible, DossierMedical, OrdonnanceInvalide).
Concepts POO appliqués :

Encapsulation : attributs privés + validations dans setters.
Héritage : hiérarchie Personne -> PersonnelMedical -> Medecin/Infirmier.
Polymorphisme : afficherProfil() redéfini dans les sous-classes.
Abstraction : Personne abstraite.
Surcharge : constructeurs de Consultation / Ordonnance.
Exceptions métier : package dédié + try/catch dans Main.

## Table des matières:
1- Ajouter un patient
2- Ajouter un médecin
3- Ajouter un infirmier
4- Créer une consultation
5- Ajouter une ordonnance
6- Afficher les patients
7- Afficher les médecins
8- Afficher les consultations
9- Consulter le dossier patient
10- Afficher le tableau de bord
11- Terminer une consultation
0- Quitter l’application


## Objectives:
- Gérer les patients (création, profil, dossier médical, antécédents).
- Gérer le personnel médical (médecins et infirmiers).
- Planifier les consultations avec contrôle de disponibilité du médecin.
- Créer et valider les ordonnances avec médicaments prescrits.
- Sécuriser les données via validations et exceptions métier.
- Fournir une interface console simple via un menu interactif.
- Suivre l’activité de la clinique (effectifs, consultations, revenus du jour).


## Caractéristiques
- Application console Java orientée objet.
- Architecture en packages (clinique, exception).
- Encapsulation avec validations dans les setters.
- Héritage (Personne → PersonnelMedical → Medecin/Infirmier).
- Polymorphisme via afficherProfil() redéfini.
- Abstraction avec classe Personne abstraite.
- Gestion d’exceptions métier personnalisées.
- Menu interactif avec saisie contrôlée.
- Gestion complète consultation/ordonnance.
- Tableau de bord (comptages + revenus du jour).

  
## Étapes de Développement
- Analyser le cahier des charges du mini-projet.
- Concevoir le modèle UML (classes et relations).
- Créer les classes de base (Personne, Patient, PersonnelMedical).
- Implémenter les classes métiers (Medecin, Infirmier, Consultation, Ordonnance, Medicament).
- Ajouter les validations des données dans les setters.
- Créer les exceptions métier dans le package exception.
- Développer la classe CliniqueMedicale pour centraliser la logique de gestion.
- Construire le menu interactif dans Main.
- Tester chaque fonctionnalité (ajout, recherche, consultation, ordonnance, tableau de bord).
- Corriger les erreurs et améliorer les messages utilisateur.
- Finaliser le projet (README, nettoyage, vérification de compilation/exécution).
   
## Tests
Testé avec des scénarios incluant l'insertion et l'affichage.
<img width="1402" height="803" alt="Screenshot 2026-05-06 123002" src="https://github.com/user-attachments/assets/5c64ba88-90ae-48ef-9bf7-eb0e99e17623" />
<img width="705" height="427" alt="Screenshot 2026-05-06 135949" src="https://github.com/user-attachments/assets/b4ca79df-7aeb-433e-860b-c251f2dd2154" />
<img width="1169" height="479" alt="Screenshot 2026-05-06 140140" src="https://github.com/user-attachments/assets/5926775f-4a1b-4f8a-8d43-4309a3519ba9" />
<img width="1337" height="686" alt="Screenshot 2026-05-06 122242" src="https://github.com/user-attachments/assets/093d278a-dc0d-4c53-9ca8-39d31eea1392" />
<img width="1087" height="532" alt="Screenshot 2026-05-06 122353" src="https://github.com/user-attachments/assets/1dc4b5fb-5086-4e3b-91e7-43c8053a5c0e" />
<img width="863" height="466" alt="Screenshot 2026-05-06 122435" src="https://github.com/user-attachments/assets/b7e14594-1c62-4f3b-969c-1d310bdc8c21" />
<img width="769" height="472" alt="Screenshot 2026-05-06 122506" src="https://github.com/user-attachments/assets/02c4c20d-a357-4484-82d6-be9c7248ea71" />
<img width="678" height="452" alt="Screenshot 2026-05-06 122540" src="https://github.com/user-attachments/assets/7587f015-ca09-49a7-9dae-aa4876cf98a3" />
<img width="1112" height="483" alt="Screenshot 2026-05-06 122624" src="https://github.com/user-attachments/assets/b109f2b0-d4d2-4a85-9b91-f3829679e157" />
<img width="711" height="664" alt="Screenshot 2026-05-06 122701" src="https://github.com/user-attachments/assets/47ddfe32-5dd5-45a9-a107-6b75835c9810" />
<img width="816" height="477" alt="Screenshot 2026-05-06 122734" src="https://github.com/user-attachments/assets/84d042ae-809c-4d3f-a962-1182ecc40962" />
maintenant testant l'exceptions
<img width="979" height="92" alt="image" src="https://github.com/user-attachments/assets/0aa42ad4-c9fd-4076-9866-2bce9a9d139a" />
<img width="1116" height="117" alt="image" src="https://github.com/user-attachments/assets/23ae53c0-316e-42ff-91d1-47a2726a8637" />
<img width="726" height="138" alt="image" src="https://github.com/user-attachments/assets/8d92b46c-9841-453f-9568-c084fd864235" />
<img width="899" height="103" alt="image" src="https://github.com/user-attachments/assets/fd607b2e-fe38-4ca5-8cec-09f4f0589850" />
<img width="967" height="65" alt="image" src="https://github.com/user-attachments/assets/4e07fea0-ac1c-4a95-a829-c4f7b723fff2" />
<img width="1127" height="69" alt="image" src="https://github.com/user-attachments/assets/d16706f5-95cd-48e9-b6c5-48b907f3044e" />
<img width="990" height="125" alt="image" src="https://github.com/user-attachments/assets/be623825-aa62-43a6-ab31-38612f9952a1" />



## Remerciements
Merci à mon instructeur "Dr.SOLTANI HAMA " et à mes camarades pour leur soutien.

## Informations de Contact
Pour toute question, contactez-moi à : amanidz2tt@gmail.com

## Team
AMANI, AMIRA, IMENE, MOHAMED
