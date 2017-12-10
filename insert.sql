insert into prvenstvo(naziv,broj_timova,broj_staza,popularnost)
values ('MATF++',4,5,'velika'),('ETF prvenstvo',5,3,'srednja'),('Sampionat UB',6,4,'mala'),('Trka Formula 4000',3,3,null);

insert into tim(ime)
values ('Informaticari'),('Numericari'),('Anonimni'),('RTI-ovci');

insert into staza(lokacija,broj_krugova,duzina_kruga,broj_krivina,mesta_za_preticanje)
values ('Dorcol',10,10,null,null),('Vracar',8,7,6,null),('Novi Beograd',10,15,null,5),('Zemun',7,20,9,6),('Zvezdara',1,1,1,1),('Pancevo',1,1,1,1),('Ada Ciganlija',1,1,1,1);

insert into trka(id_prvenstva,id_staze)
values (1,1),(1,3),(1,4),(1,5),(1,7),(2,2),(2,5),(2,7),(3,1),(3,2),(3,4),(3,7),(4,5),(4,6),(4,7);

insert into ucestvovanje(id_prvenstva,id_tima)
values (1,1),(1,2),(1,3),(1,4),(1,5),(2,6),(2,7),(2,8),(2,1),(2,3),(3,1),(3,2),(3,3),(3,6),(3,8),(3,5),(4,1),(4,7),(4,8);

insert into sponzor(ime,marketing,brend)
values ('Koka-kola','odlican','visok'),('Telekom Srbija','srednji','visok'),('Fruvita','odlican','srednji'),('Mlekara Granice','srednji','srednji'),('Spadijer programming','srednji','nizak');

insert into sponzorski_pul(id_tima,id_sponzora)
(1,1),(1,5),(2,2),(2,3),(2,4),(3,3),(3,5),(3,2),(4,5),(5,1),(5,3),(6,2),(6,3),(6,4),(7,1),(7,4);

insert into vlasnik(ime,prezime,saldo,kriminalna_proslost,redovna_isplata)
values ('Petar','Petrovic',1000000,'ne','da'),('Marko','Markovic',2000000,'ne',null),('Nikola','Nikolic',5000000,'ne','ne'),('Anon','Imni',10000000,'da',null);

insert into vlasnistvo(id_tima,id_vlansika)
values (1,1),(1,2),(2,3),(3,1),(4,2),(4,3),(5,4),(6,2),(6,1),(7,3),(8,3);

insert into mehanicar(broj_licence,ime,prezime,struka,staz)
values (165379,'Milan','Milovanovic','vulkanizer',4),(147689,'Jovan','Jovanovic','limar',2),(982973,'David','Davidovic','vulkanizer',7),(154328,'Lazar','Lazarevic','vulkanizer',2),(125348,'Kosta','Kostic','limar',1),(341259,'Bojan','Bojanic','kocnice');

insert into odrzavanje(id_tima,id_mehanicara)
values (1,165379),(1,147689),(1,341259),(2,982973),(2,147689),(2,341259),(3,165379);

insert into motor(broj_motora,proizvodjac,zapremina,radna_temperatura,snaga,broj_obrtaja,pouzdanost)
values (184765890,'Alfa Romeo',3500,70,800,17000,'dobra'),(134532673,'Alfa Romeo',3600,80,830,18000,'odlicna'),(436347635,'BMW',3300,74,800,19000,'odlicna'),(829381248,'BMW',4000,90,890,19800,'srednja'),(435803484,'BMW',3900,85,840,18000,'dobra'),(736586803,'Ford',3500,70,800,17300,'odlicna'),(265860448,'Ford',4100,80,885,20000,'dobra'),(152489028,'Ford',3800,83,820,19000,'odlicna'),(183749127,'Ford',4300,95,900,20000,'srednja'),(234135675,'Honda',3500,70,800,17000,'dobra'),(265829480,'Honda',3600,80,830,18000,'odlicna'),(765284910,'Honda',3300,74,800,19000,'odlicna'),(123633456,'Lamborgini',4000,90,890,19800,'dobra'),(120394012,'Mercedes',3900,85,840,18000,'dobra'),(124918420,'Mercedes',3500,70,800,17300,'odlicna'),(679273491,'Porse',4100,80,885,20000,'dobra'),(341234622,'Pezo',3800,83,820,19000,'odlicna'),(454312345,'Reno',3800,88,870,18900,'dobra');

insert into formula(broj_sasije,proizvodjac,maks_brzina,tezina,duzina,motor,tim)
values (324829102,'Ferari',380,800,4600,183749127,1),(239482349,'Vilijams',370,820,4750,123633456,1),(753890234,'Mercedes',365,800,4600,120394012,2),(123642936,'Reno',370,830,4750,454312345,2),(235412352,'Ford',380,800,4600,183749127,3),(981024892,'Ford',360,840,4700,736586803,3),(324123546,'Ford',365,800,4600,265860448,4),(212345234,'BMW',375,840,4820,829381248,4);

insert into paket_guma(formula,proizvodjac,tip,velicina,radna_temperatura)
values (324829102,'Pireli','suvo',12,90),(239482349,'Gudjer','mokro',13,70),(753890234,'Pireli','suvo',11,93),(123642936,'Danlop','mokro',13,75),(235412352,'Pireli','suvo',14,95),(981024892,'Gudjer','mokro',15,75),(324123546,'Danlop','suvo',14,94),(212345234,'Pireli','mokro',12,77);

--nijedna od narednih naredbi ne bi smela da se izvrsi, zbog aktiviranja okidaca
insert into trka(id_prvenstva,id_staze)
values (1,6);

insert into ucestvovanje(id_prvenstva,id_tima)
values (1,7);
