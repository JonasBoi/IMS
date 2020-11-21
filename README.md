# IMS
## FIT VUT - IMS projekt

### Téma č. 8: Diskrétní model výrobního procesu (SHO)
Nastudujte výrobní proces konkrétního výrobku, případně konkrétního výrobního provozu.
Modelujte jako SHO. Demonstrujte efektivitu výroby, úzká místa, hrozby apod.

### Odevzdané soubory:
* simulacni_studie.pdf - dokumentace projektu
* ims.cc - zdrojový kód programu
* Makefile - makefile pro předklad programu
* README.md
* diagramy_a_grafy - adresář s diagramy a grafy použitými v simulační studii

### Překlad a spuštění:
make - překlad
make run - základní bezparametrické spuštění

#### spouštění s parametry:
**./ims** [-help] [**-t** počet dní] [**-x**] [**-s** transakcí] [**-a...i** minut] [**-j...r** minut] [**-v**]

Pro podrobný popis všech parametrů viz simulační studie, kapitola 4 - Implementace.
