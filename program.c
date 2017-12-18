#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <stdarg.h>
#include <errno.h>

#define QUERY_SIZE 513

#define BUFFER_SIZE 46

#define BROJ_OPCIJA 3

/* Funkcija error_fatal() ispisuje poruku o gresci i potom prekida program. */
static void error_fatal(char *format,...);

void ispisi(MYSQL_RES *rezultat);

int ponudi_opcije(int opcija);

void formiraj_upit(int p,char *query,MYSQL *konekcija);

int main(int argc,char *argv[])
{
  MYSQL *konekcija;	/* Promenljiva za konekciju. */
  MYSQL_RES *rezultat;	/* Promenljiva za rezultat. */

  char query[QUERY_SIZE];	/* Promenljiva za formuaciju upita. */

  /* Incijalizuje se promenljiva koja ce predstavljati konekciju. */
  konekcija = mysql_init(NULL);
  
  /* Pokusava se sa konektovanjem na bazu. */
  if(mysql_real_connect(konekcija,"localhost","root","","formula4000",0,NULL,0) == NULL)
      error_fatal("Greska u konekciji. %s\n", mysql_error(konekcija));

  printf("Uspesno povezivanje na bazu\n");

  while(1)
  {
    int opcija=1,p;
    printf("\n");
    printf("Odaberite jednu od sledecih opcija (0 za kraj programa):\n");
    printf("%d. Ispis podataka\n",opcija++);
    printf("%d. Unos podataka\n", opcija++);
    printf("%d. Izmena podataka\n", opcija++);
    scanf("%d",&opcija);
    printf("\n");

    if(opcija==0)
      break;

    p=ponudi_opcije(opcija);

    if(p==-1)
      continue;

    formiraj_upit(p,query,konekcija);

    printf("%s\n",query);

    /* Pokusava se sa izvrsavanjem upita. */
    if(mysql_query(konekcija, query) != 0)
      error_fatal("Greska u upitu %s\n", mysql_error(konekcija));

    switch(opcija)
    {
      case 1:
        rezultat = mysql_use_result(konekcija);
        ispisi(rezultat);
        mysql_free_result(rezultat);
        break;
      case 2:
        if(mysql_affected_rows(konekcija)==1)
          printf("Uspesno je unet podatak u bazu.\n");
        break;
    }
  }

  /* Zatvara se konekcija. */
  mysql_close(konekcija);

  /* Zavrsava se program */
  exit(EXIT_SUCCESS);
}

void formiraj_upit(int p,char *query,MYSQL *konekcija)
{
  char buffer1[BUFFER_SIZE],buffer2[BUFFER_SIZE],buffer3[BUFFER_SIZE],buffer4[BUFFER_SIZE];
  int a,b,c,d,e,f;
  MYSQL_RES *rezultat;
  switch(p%BROJ_OPCIJA)
  {
    case 0:
      switch(p/BROJ_OPCIJA)
      {
        case 1:
          sprintf(query,"select * from formula");
          break;
        case 2:
          sprintf(query,"select * from vozac");
          break;
        case 3:
          sprintf(query,"select * from menadzer");
          break;
        case 4:
          sprintf(query,"select * from sponzor");
          break;
        case 5:
          sprintf(query,"select * from vlasnik");
          break;
        case 6:
          sprintf(query,"select * from mehanicar");
          break;
        case 7:
          sprintf(query,"select id_tima,t.ime as ime_tima,v.ime as ime_vozaca,prezime as prezime_vozaca from tim as t join vozac as v on id_tima=tim");
          break;
        case 8:
          sprintf(query,"select broj_sasije,proizvodjac,maks_brzina,t.ime as ime_tima,v.ime as ime_vozaca,prezime as prezime_vozaca from formula as f join tim as t on f.tim=id_tima join vozac as v on broj_sasije=formula");
          break;
        case 9:
          sprintf(query,"select broj_sasije,f.proizvodjac as proizvodjac_formule,maks_brzina,pg.proizvodjac as proizvodjac_guma,tip,velicina,radna_temperatura,trajanje from formula as f join paket_guma as pg on broj_sasije=formula");
          break;
        case 10:
          sprintf(query,"select broj_sasije,f.proizvodjac as proizvodjac_formule,maks_brzina,m.proizvodjac as proizvodjac_motora,zapremina,radna_temperatura,snaga,broj_obrtaja,pouzdanost from formula as f join motor as m on motor=broj_motora");
          break;
        case 11:
          sprintf(query,"select t.ime as ime_tima,s.ime as ime_sponzora,marketing,brend,trajanje from tim as t join sponzorski_pul as sp on t.id_tima=sp.id_tima join sponzor as s on s.id_sponzora=sp.id_sponzora order by t.id_tima");
          break;
        case 12:
          sprintf(query,"select t.ime as ime_tima,v.ime as ime_vlasnika,v.prezime as prezime_vlasnika,saldo,kriminalna_proslost,redovna_isplata,trajanje from tim as t join vlasnistvo as vl on t.id_tima=vl.id_tima join vlasnik as v on v.id_vlasnika=vl.id_vlasnika order by t.id_tima");
          break;
        case 13:
          sprintf(query,"select t.ime as ime_tima,m.ime as ime_mehanicara,prezime as prezime_mehanicara,struka,staz,prethodni_poslovi,poslednji_servis from tim as t join odrzavanje as o on t.id_tima=o.id_tima join mehanicar as m on broj_licence=id_mehanicara order by t.id_tima");
          break;
        default:
          printf("Pogresna opcija.\n");
          return;
      }
       break;
    case 1:
      switch(p/BROJ_OPCIJA)
      {
        case 1:
          if(mysql_query(konekcija, "select broj_sasije from formula order by 1") != 0)
            error_fatal("Greska u upitu %s\n", mysql_error(konekcija));
          rezultat = mysql_use_result(konekcija);
          ispisi(rezultat);
          mysql_free_result(rezultat);

          printf("Unesite broj sasije (ne sme biti neki od gore navedenih): ");
          scanf("%d",&a);
          printf("Unesite proizvodjaca: ");
          scanf("%s",buffer1);
          printf("Unesite maksimalnu brzinu: ");
          scanf("%d",&b);
          printf("Unesite tezinu: ");
          scanf("%d",&c);
          printf("Unesite duzinu: ");
          scanf("%d",&d);
          
          if(mysql_query(konekcija, "select * from motor where broj_motora not in (select motor from formula)") != 0)
            error_fatal("Greska u upitu %s\n", mysql_error(konekcija));
          rezultat = mysql_use_result(konekcija);
          ispisi(rezultat);
          mysql_free_result(rezultat);

          printf("Unesite broj motora (ponudjeni motori su slobodni): ");
          scanf("%d",&e);
          
          if(mysql_query(konekcija, "select * from tim order by id_tima") != 0)
            error_fatal("Greska u upitu %s\n", mysql_error(konekcija));
          rezultat = mysql_use_result(konekcija);
          ispisi(rezultat);
          mysql_free_result(rezultat);

          printf("Unesite identifikator tima: ");
          scanf("%d",&f);

          sprintf(query,"insert into formula values (%d,'%s',%d,%d,%d,%d,%d)",a,buffer1,b,c,d,e,f);
          break;

        case 2:
          printf("Unesite ime: ");
          scanf("%s",buffer1);
          printf("Unesite prezime: ");
          scanf("%s",buffer2);
          printf("Unesite godinu rodjenja: ");
          scanf("%d",&a);
          printf("Unesite visinu: ");
          scanf("%d",&b);
          printf("Unesite tezinu: ");
          scanf("%d",&c);

          if(mysql_query(konekcija, "select * from menadzer") != 0)
            error_fatal("Greska u upitu %s\n", mysql_error(konekcija));
          rezultat = mysql_use_result(konekcija);
          ispisi(rezultat);
          mysql_free_result(rezultat);
          printf("Unesite identifikator menadzera ili -1 ako vozac nema menadzеra: ");
          scanf("%d",&d);

          if(mysql_query(konekcija, "select * from tim") != 0)
            error_fatal("Greska u upitu %s\n", mysql_error(konekcija));
          rezultat = mysql_use_result(konekcija);
          ispisi(rezultat);
          mysql_free_result(rezultat);
          printf("Unesite identifikator tima ili -1 ako vozac trenutno ne vozi ni u jednom timu: ");
          scanf("%d",&e);

          if(e!=-1)
          {
            char upit[QUERY_SIZE];
            sprintf(upit,"select * from formula where tim=%d",e);
            if(mysql_query(konekcija,upit) != 0)
              error_fatal("Greska u upitu %s\n", mysql_error(konekcija));
            rezultat = mysql_use_result(konekcija);
            ispisi(rezultat);
            mysql_free_result(rezultat);
            printf("Unesite broj sasije formule koju vozac vozi ili -1 ako trenutno ne vozi nijednu formulu: ");
            scanf("%d",&f);
          }
          else f=-1;

          sprintf(query,"insert into vozac(ime,prezime,godina_rodjenja,visina,tezina,menadzer,tim,formula) values ('%s','%s',%d,%d,%d,",buffer1,buffer2,a,b,c);
          if(d==-1)
            strcat(query,"null,");
          else
          {
            sprintf(buffer3,"%d,",d);
            strcat(query,buffer3);
          }
          if(e==-1)
            strcat(query,"null,");
          else
          {
            sprintf(buffer3,"%d,",e);
            strcat(query,buffer3);
          }
          if(f==-1)
            strcat(query,"null)");
          else
          {
            sprintf(buffer3,"%d)",f);
            strcat(query,buffer3);
          }
          break;

        case 3:
          printf("Unesite ime: ");
          scanf("%s",buffer1);
          printf("Unesite broj \"vezа\" (-1 ukoliko nije poznat): ");
          scanf("%d",&a);

          sprintf(query,"insert into menadzer(ime,veze) values ('%s',",buffer1);
          if(a==-1)
            strcat(query,"null)");
          else
          {
            sprintf(buffer2,"%d)",a);
            strcat(query,buffer2);
          }
          break;

        case 4:
          printf("Unesite ime: ");
          scanf("%s",buffer1);
          printf("Unesite marketinsku sposobnost (odlican,srednji,los): ");
          scanf("%s",buffer2);
          printf("Unesite prepoznatljivost (brend) (visok,srednji,nizak): ");
          scanf("%s",buffer3);

          sprintf(query,"insert into sponzor(ime,marketing,brend) values ('%s','%s','%s')",buffer1,buffer2,buffer3);
          break;
      }
      break;
    case 2:
      switch(p/BROJ_OPCIJA)
      {
        case 1:
          break;
      }
    default:
      printf("Ovo je neka magija\n");
      return;
  }
}

int ponudi_opcije(int opcija)
{
  int p,pom;
  switch(opcija)
  {
    case 0:
      return 0;
    case 1:
      pom=1;
      printf("%d. Ispis formula\n",pom++);
      printf("%d. Ispis vozaca\n",pom++);
      printf("%d. Ispis menadzera\n",pom++);
      printf("%d. Ispis sponzora\n",pom++);
      printf("%d. Ispis vlasnika\n",pom++);
      printf("%d. Ispis mehanicara\n",pom++);
      printf("%d. Ispis timova i vozaca\n",pom++);
      printf("%d. Ispis formula, timova i vozaca\n",pom++);
      printf("%d. Ispis informacija o gumama\n",pom++);
      printf("%d. Ispis informacija o motorima na formulama\n",pom++);
      printf("%d. Ispis sponzora timova\n",pom++);
      printf("%d. Ispis vlasnika timova\n",pom++);
      printf("%d. Ispis mehanicara timova\n",pom++);
      scanf("%d",&pom);
      printf("\n");
      p=BROJ_OPCIJA*pom;
      break;
    case 2:
      pom=1;
      printf("%d. Unos formule\n",pom++);
      printf("%d. Unos vozaca\n",pom++);
      printf("%d. Unos menadzera\n",pom++);
      printf("%d. Unos sponzora\n",pom++);
      printf("%d. Unos vlasnika\n",pom++);
      printf("%d. Unos mehanicara\n",pom++);
      printf("%d. Unos tima\n",pom++);
      scanf("%d",&pom);
      printf("\n");
      p=BROJ_OPCIJA*pom+1;
      break;
    default:
      printf("Pogresna opcija!\n");
      p=-1;
      break;
  }
  return p;
}

void ispisi(MYSQL_RES *rezultat)
{
  MYSQL_ROW red;	/* Promenljiva za jedan red rezultata. */
  MYSQL_FIELD *polje;	/* Promenljiva za nazive kolona. */
  int i;		/* Brojac u petljama. */
  int broj;		/* Pomocna promenljiva za broj kolona. */	
  
  /* Ispisuje se zaglavlje kolone. */
  polje = mysql_fetch_field(rezultat);

  /* Racuna se broj kolona. */
  broj = mysql_num_fields(rezultat);

  red = mysql_fetch_row(rezultat);

  if(red==0)
  {
    printf("Tabela je prazna.\n");
    return;
  }

  for(i = 0; i < broj; i++)
    printf("%-20s ", polje[i].name);
  printf("\n");

  /* Ispisuju se vrednosti. */
  do
  {
    for(i = 0; i < broj; i++)
      printf("%-20s ", red[i]);
    printf("\n");
  }
  while((red = mysql_fetch_row(rezultat))!=0);
}

static void error_fatal(char *format,...)
{
  va_list arguments;		/* Lista argumenata funkcije. */

  /* Stampa se string predstavljen argumentima funkcije. */
  va_start(arguments, format);
  vfprintf(stderr, format, arguments);
  va_end(arguments);

  /* Prekida se program. */
  exit(EXIT_FAILURE);
}
