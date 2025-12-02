
#include "mainwindowex3.h"
#include "ui_mainwindowex3.h"
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>
#include <stdio.h>

int descriptor;

MainWindowEx3::MainWindowEx3(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindowEx3)
{
    ui->setupUi(this);
}

MainWindowEx3::~MainWindowEx3()
{
    delete ui;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions utiles : ne pas modifier /////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx3::setGroupe1(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe1->clear();
    return;
  }
  ui->lineEditGroupe1->setText(Text);
}

void MainWindowEx3::setGroupe2(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe2->clear();
    return;
  }
  ui->lineEditGroupe2->setText(Text);
}

void MainWindowEx3::setGroupe3(const char* Text)
{
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditGroupe3->clear();
    return;
  }
  ui->lineEditGroupe3->setText(Text);
}

void MainWindowEx3::setResultat1(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat1->clear();
    return;
  }
  ui->lineEditResultat1->setText(Text);
}

void MainWindowEx3::setResultat2(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat2->clear();
    return;
  }
  ui->lineEditResultat2->setText(Text);
}

void MainWindowEx3::setResultat3(int nb)
{
  char Text[20];
  sprintf(Text,"%d",nb);
  fprintf(stderr,"---%s---\n",Text);
  if (strlen(Text) == 0 )
  {
    ui->lineEditResultat3->clear();
    return;
  }
  ui->lineEditResultat3->setText(Text);
}

bool MainWindowEx3::recherche1Selectionnee()
{
  return ui->checkBoxRecherche1->isChecked();
}

bool MainWindowEx3::recherche2Selectionnee()
{
  return ui->checkBoxRecherche2->isChecked();
}

bool MainWindowEx3::recherche3Selectionnee()
{
  return ui->checkBoxRecherche3->isChecked();
}

const char* MainWindowEx3::getGroupe1()
{
  if (ui->lineEditGroupe1->text().size())
  { 
    strcpy(groupe1,ui->lineEditGroupe1->text().toStdString().c_str());
    return groupe1;
  }
  return NULL;
}

const char* MainWindowEx3::getGroupe2()
{
  if (ui->lineEditGroupe2->text().size())
  { 
    strcpy(groupe2,ui->lineEditGroupe2->text().toStdString().c_str());
    return groupe2;
  }
  return NULL;
}

const char* MainWindowEx3::getGroupe3()
{
  if (ui->lineEditGroupe3->text().size())
  { 
    strcpy(groupe3,ui->lineEditGroupe3->text().toStdString().c_str());
    return groupe3;
  }
  return NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///// Fonctions clics sur les boutons ////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MainWindowEx3::on_pushButtonLancerRecherche_clicked()
{
  // TO DO
  descriptor = open("Trace.log", O_CREAT | O_TRUNC | O_WRONLY, 0666);
  dup2(descriptor, STDERR_FILENO);
  fprintf(stderr,"Clic sur le bouton Lancer Recherche\n");
  int idFils1,idFils2,idFils3;
  int status;
  if(recherche1Selectionnee()){
    idFils1 = fork();
    if (idFils1 == 0) {
      const char* groupe = getGroupe1();
      char* args[] = {(char*)"Lecture", (char*)groupe, NULL};
      execv("Lecture", args);
    }
  }
  if(recherche2Selectionnee()){
    idFils2 = fork();
    if (idFils2 == 0) {
      const char* groupe = getGroupe2();
      char* args[] = {(char*)"Lecture", (char*)groupe, NULL};
      execv("Lecture", args);
    }
  }
  if(recherche3Selectionnee()){
    idFils3 = fork();
    if (idFils3 == 0) {
      const char* groupe = getGroupe3();
      char* args[] = {(char*)"Lecture", (char*)groupe, NULL};
      execv("Lecture", args);
    }
  }

  

  while(true){
    fprintf(stderr,"Avant wait...\n");
    int finishedPid = wait(&status);
    if(finishedPid == -1){
      break;
    }
    fprintf(stderr,"Apres wait...\n");

    if (finishedPid == idFils1) {
      setResultat1(WEXITSTATUS(status));
    } else if (finishedPid == idFils2) {
      setResultat2(WEXITSTATUS(status));
    } else if (finishedPid == idFils3) {
      setResultat3(WEXITSTATUS(status));
    }
  }

}

void MainWindowEx3::on_pushButtonVider_clicked()
{
  // TO DO
  fprintf(stderr,"Clic sur le bouton Vider\n");
  setGroupe1("");
  setGroupe2("");
  setGroupe3("");
  ui->lineEditResultat1->clear();
  ui->lineEditResultat2->clear();
  ui->lineEditResultat3->clear();
}

void MainWindowEx3::on_pushButtonQuitter_clicked()
{
  // TO DO
  fprintf(stderr,"Clic sur le bouton Quitter\n");
  ::close(descriptor);  
  exit(0);
}
