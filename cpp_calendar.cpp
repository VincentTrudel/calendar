/*

Auteur		: Vincent Trudel
Description	: TP7
Version		: 1.0

*/

#include <iostream>  // pour le cout
#include <conio.h>   // pour le _getch()
#include <iomanip>   // pour le cadrage
#include <string>    // pour les strings
#include "C:/cvm.h"

using namespace std;

void main()
{
	//VARIABLES
	int JJ;
	int MM;
	int AAAA;
	int nbTotalJoursEcoules, jourSemaine, nbJoursDansMois;
	int mois_precedent;
	int colonneDepartJour;
	int jour; 
	int x_colonne;
	int bordure;
	bool DateValide, anneeBissextile;

	string DateStr;
	string JourDeLaSemaine;
	string Mois;
	string JourAbbrev;

	char reponseCalendrier, reponseAutreDate;

	//CONSTANTES

	string ENTREZUNEDATE = "Entrez une date (JJ/MM/AAAA) : ";
	string JOURERRONE = "Le jour doit \210tre entre 1 et 31 inclusivement";
	string MOISERRONE = "Le mois est erron\202(doit \210tre entre 1 et 12 inclusivement)";
	string ANNEEERRONEE = "L'ann\202e est erron\202e (de 1901 \205 2099 seulement)";
	string ERREURFEVRIER = "Le mois de f\202vrier ne peut compter plus de 28 jours";
	string QUESTIONCALENDRIER = "Voulez-vous voir le calendrier complet du mois (O/N) ?";
	string QUESTIONAUTREDATE = "Voulez-vous traiter une autre date (O/N) ?";
	string ERREURFORMAT = " ERREUR: Entrez une date valide selon le format !";
	string AUREVOIR = "A U R E V O I R !";

	char bordureTableau = '_';

	int milieuEcran = 60; // 120/2
	int x_debutTableau = 30;
	int y_debutTableau = 6;
	int x_finTableau = 91;

	//TRAITEMENT

	do
	{ 
		do 
		{

		entrezunedate:

			while (_kbhit()) _getch();			// vider le tampon du clavier
			cin.ignore(cin.rdbuf()->in_avail());	// vider le tampon du cin
			cin.clear();  // remettre en marche le cin
			gotoxy(4, 1);
			cout << ENTREZUNEDATE;
			
			cin.ignore(0, '/');
			cin >> JJ;

			if (cin.fail())
			{ 
				gotoxy(4, 1);
				clreoscr();
				gotoxy(4, 29);
				cout << ERREURFORMAT;
				goto entrezunedate;
			}
			else
			{ 
				cin.clear();
				cin.ignore(2, '/');
				cin >> MM;
				if (cin.fail())
				{
					gotoxy(4, 1);
					clreoscr();
					gotoxy(4, 29);
					cout << ERREURFORMAT;
					goto entrezunedate;
				}
				else
				{ 
					cin.clear();
					cin.ignore(6, '/');
					cin >> AAAA;

					if (cin.fail())
					{
						gotoxy(4, 1);
						clreoscr();
						gotoxy(4, 29);
						cout << ERREURFORMAT;
						goto entrezunedate;
					}
					else
					{ 
						DateValide = false;

						anneeBissextile = ((AAAA % 4 == 0) && (AAAA % 100 != 0)) || AAAA % 400 == 0;

						//else
						if (!(JJ >= 1 && JJ <= 31))
						{
							clrscr();
							gotoxy(4, 29);
							cout << JOURERRONE;
						}
						else
							if (!(MM >= 1 && MM <= 12))
							{
								clrscr();
								gotoxy(4, 29);
								cout << MOISERRONE;
							}
							else
								if (!(AAAA >= 1901 && AAAA <= 2099))
								{
									clrscr();
									gotoxy(4, 29);
									cout << ANNEEERRONEE;
								}
								else
									if ((MM == 2 && JJ > 28) && !(JJ == 29 && anneeBissextile))
									{
										clrscr();
										gotoxy(4, 29);
										cout << ERREURFEVRIER;
									}
									else
										DateValide = true;					
					}
				}
			}
		} while (!DateValide);

		mois_precedent = MM - 1;

		nbTotalJoursEcoules = mois_precedent * 31; //On traite chaque mois comme s'il avait 31 jours

		if (mois_precedent >= 4) //Avril, le mois 4, a 30 jours, donc il faut soustraire 1 jour si avril est dans le calcul
		{ 
			nbTotalJoursEcoules--;
			if (mois_precedent >= 6) //Juin
			{
				nbTotalJoursEcoules--;
				if (mois_precedent >= 9) //Septembre
				{
					nbTotalJoursEcoules--;
					if(mois_precedent >= 11)//Novembre
						nbTotalJoursEcoules--;
				}
			}
		}

		//Février
		if (mois_precedent >= 2)
		{ 
			if (anneeBissextile) //31-2 = 29 jours en février si l'année est bissextile
				nbTotalJoursEcoules -= 2;
			else
				nbTotalJoursEcoules -= 3; //31-2 = 28 si l'année n'est pas bissextile
		}

		nbTotalJoursEcoules += JJ;

		jourSemaine = (nbTotalJoursEcoules + (AAAA - 1900) + (AAAA - 1901) / 4) % 7 + 1;
		
		switch (jourSemaine) 
		{
		case 1: JourDeLaSemaine = "Dimanche";break;
		case 2: JourDeLaSemaine = "Lundi"; break;
		case 3: JourDeLaSemaine = "Mardi"; break;
		case 4: JourDeLaSemaine = "Mercredi"; break;
		case 5: JourDeLaSemaine = "Jeudi"; break;
		case 6: JourDeLaSemaine = "Vendredi"; break;
		case 7: JourDeLaSemaine = "Samedi"; break;
		}

		if (JJ >= 7)
		{
			if (JJ % 7 == 1)
				colonneDepartJour = jourSemaine;

			else
			{
				colonneDepartJour = jourSemaine - (JJ % 7 -1);
				if (colonneDepartJour <= 0)
					colonneDepartJour = colonneDepartJour +=7;
			}
		}
		else
		{ 
			colonneDepartJour = jourSemaine - (JJ - 1);
			if (colonneDepartJour <= 0)
				colonneDepartJour = colonneDepartJour += 7;
		}

		clrscr();
		cout << "\n\n\n";
		cout << "\tLe " << JJ << '/' << MM << '/' << AAAA << " est un : " << JourDeLaSemaine << endl << endl << endl;
		cout << "\t" << QUESTIONCALENDRIER;

		do
		{
			reponseCalendrier = _getche();
			reponseCalendrier = toupper(reponseCalendrier);
			cout << "\b";

		} while ((reponseCalendrier != 'O') && (reponseCalendrier != 'N'));

		//TABLEAU
		if( reponseCalendrier == 'O' )
		{ 

			switch(MM)
			{ 
			case 1: Mois = "Janvier"; nbJoursDansMois = 31; break;
			case 2: Mois = "F\202vrier";
				if (anneeBissextile)
					nbJoursDansMois = 29;
				else
					nbJoursDansMois = 28; break;
			case 3: Mois = "Mars"; nbJoursDansMois = 31; break;
			case 4: Mois = "Avril"; nbJoursDansMois = 30; break;
			case 5: Mois = "Mai"; nbJoursDansMois = 31; break;
			case 6: Mois = "Juin"; nbJoursDansMois = 30; break;
			case 7: Mois = "Juillet"; nbJoursDansMois = 31; break;
			case 8: Mois = "Aout"; nbJoursDansMois = 31; break;
			case 9: Mois = "Septembre"; nbJoursDansMois = 30; break;
			case 10: Mois = "Octobre"; nbJoursDansMois = 31; break;
			case 11: Mois = "Novembre"; nbJoursDansMois = 30; break;
			case 12: Mois = "D\202cembre"; nbJoursDansMois = 31; break;
			}
			clrscr();
			gotoxy(milieuEcran, 3);

			cout << Mois << ' ' << AAAA;
			
			gotoxy(29, 24);

			jour = 1;


			for (int rangee = y_debutTableau; rangee <= (y_debutTableau + 3 + (((nbJoursDansMois / 7) + 1) * 2)+1); rangee++)
			{
				for (int colonne = 1; colonne <= 7; colonne++)
				{
					x_colonne = x_debutTableau - 10 + 10 * (colonne);

					gotoxy(x_colonne, rangee);

					bordure = 0;

					switch (colonne)
					{
					case 1: JourAbbrev = "Di"; bordure = 10; break;
					case 2: JourAbbrev = "Lu"; bordure = 10; break;
					case 3: JourAbbrev = "Ma"; bordure = 10; break;
					case 4: JourAbbrev = "Me"; bordure = 10; break;
					case 5: JourAbbrev = "Je"; bordure = 10; break;
					case 6: JourAbbrev = "Ve"; bordure = 10; break;
					case 7: JourAbbrev = "Sa"; bordure = 1; break;
					}

					switch (rangee) 
					{
					case 6:
						cout << JourAbbrev; 
							break;
					case 7: for (int i = 0; i <= bordure; i++)

								cout << bordureTableau;
							break;
					case 8: break;
					case 9: break;
					case 11: break;
					case 13: break;
					case 15: break;
					case 17: break;
					case 19: break;
					default: 
						if (!(rangee ==10 && colonne < colonneDepartJour) && (jour <= nbJoursDansMois)) //Changer colonne
						{ 
							cout << jour; jour++;
						}
							break;
						
					}
				}
			}
		}

		gotoxy(0, 30);

		cout << "\t" << QUESTIONAUTREDATE;
		do
		{
			reponseAutreDate = _getche();
			reponseAutreDate = toupper(reponseAutreDate);
			cout << "\b";

		} while ((reponseAutreDate != 'O') && (reponseAutreDate != 'N'));

		clrscr();

	} while (reponseAutreDate == 'O');
		
		_getch();
}