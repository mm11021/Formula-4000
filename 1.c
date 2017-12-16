#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <stdarg.h>
#include <errno.h>


#define QUERY_SIZE 260

#define BUFFER_SIZE 80

/* Funkcija error_fatal() ispisuje poruku o gresci i potom prekida program. */
static void error_fatal(char *format,...);

void ispisi(MYSQL_RES *rezultat);

int main(int argc,char *argv[])
{
  MYSQL *konekcija;	/* Promenljiva za konekciju. */
  MYSQL_RES *rezultat;	/* Promenljiva za rezultat. */

  char query[QUERY_SIZE];	/* Promenljiva za formuaciju upita. */
  char buffer[BUFFER_SIZE];	/* Velicina poruke koja se ucitava sa ulaza. */

  /* Incijalizuje se promenljiva koja ce predstavljati konekciju. */
  konekcija = mysql_init(NULL);
  
  /* Pokusava se sa konektovanjem na bazu. */
  if(mysql_real_connect(konekcija,"localhost","root","","formula4000",0,NULL,0) == NULL)
      error_fatal("Greska u konekciji. %s\n", mysql_error(konekcija));

  printf("Uspesno povezivanje na bazu\n");

  while(1)
  {
    int opcija=1;
    printf("\n");
    printf("Odaberite jednu od sledecih opcija (0 za kraj programa):\n");
    printf("%d. Ispis formula\n",opcija++);
    printf("%d. Ispis vozaca\n",opcija++);
    printf("%d. Ispis menadzera\n",opcija++);
    printf("%d. Ispis sponzora\n",opcija++);
    printf("%d. Ispis vlasnika\n",opcija++);
    printf("%d. Ispis mehanicara\n",opcija++);
    printf("%d. Ispis timova i vozaca\n",opcija++);
    printf("%d. Ispis formula, timova i vozaca\n",opcija++);
    printf("%d. Ispis informacija o gumama\n",opcija++);
    printf("%d. Ispis informacija o motorima na formulama\n",opcija++);
    printf("%d. Ispis sponzora timova\n",opcija++);
    printf("%d. Ispis vlasnika timova\n",opcija++);
    printf("%d. Ispis mehanicara timova\n",opcija++);
    scanf("%d",&opcija);
    printf("\n");

    if(opcija==0)
      break;
    switch(opcija)
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
        continue;
    }

    /* Pokusava se sa izvrsavanjem upita. */
    if(mysql_query(konekcija, query) != 0)
      error_fatal("Greska u upitu %s\n", mysql_error(konekcija));

    rezultat = mysql_use_result(konekcija);

    ispisi(rezultat);

    mysql_free_result(rezultat);
  }
  
  /* Oslobadja se trenutni rezultat, posto nam vise ne treba. */
  mysql_free_result(rezultat);

  /* Zatvara se konekcija. */
  mysql_close(konekcija);

  /* Zavrsava se program */
  exit(EXIT_SUCCESS);
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
