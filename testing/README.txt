simpleUnitTest.sh : script de test "unitaire" "boite noire" (ou "externe") minimal.

########################################
# Update Sept 2012
# Update August 2016
########################################
# No restriction on usage nor dissemination
########################################
# Problèmes, commentaires : nicolas.castagne@phelma.grenoble-inp.fr
########################################

########################################
# Lancement rapide des tests de l'incrément 1 du projet SCHEME
########################################
1/ se placer dans le répertoire de l'exécutable a tester, par exemple le répertoire scheme
2/ entrer, par exemple
	../testing/simpleUnitTest.sh -e ./scheme tests/*.scm

Ou : 
	../testing/simpleUnitTest.sh est le chemin vers script de test
	./scheme est le chemin vers l'executable a tester (scheme ici) 
	test/*.scm  designe l'ensemble des scripts scheme .scm a tester

Variante, mode batch, avec l’option -b : tous les tests sont lancés immédiatement, jusqu’au rapport final :
	../testing/simpleUnitTest.sh -e ./scheme -b tests/*.scm



Voir la suite pour des détails.


########################################
# Introduction
########################################
Le script lance un <executable> sur une liste de fichiers de <test>, l'ensemble étant passé en argument du script.


===< Chaque fichier de <test>.scm doit débuter par un COMMENTAIRE ( ; BLA BLA en Scheme) qui :
1- précise si ce test doit générer une erreur (le programme testé est censé retourné un code erreur), au moyen de :
	; TEST_RETURN_CODE=PASS
ou	; TEST_RETURN_CODE=FAIL
ou	; TEST_RETURN_CODE=DO_NOT_CHECK

Dans le premier cas PASS, on attend que le programme testé retourne 0
Dans le premier cas FAIL, on attend que le programme testé retourne un nombre différent de 0.
C’est donc que le programme testé est censé générer une erreur pour le test considéré.
Dans le dernier cas DO_NOT_CHECK, le code de retour du programme testé ne sera pas considéré.


2- donne un éventuel commentaire sur le test, précédé de TEST_COMMENT=



==> chaque fichier <test>.scm doit être accompagné d'un fichier <test>.res
	Ce fichier doit contenir la sortie standard (stdout) attendue - ce qu'est censé générer l'<executable> 
	sur sa sortie standard quand il est exécuté sur le fichier <test>.
	C'est ce fichier <test>.res qui est utilisé pour comparer la sortie attendue avec la sortie standard de l'<exécutable>.



Pour chacun des fichiers de <test> passé en argument, le script : 
	- lance l'<executable> en lui passant <test> en argument
	- détecte si l'<executable> a "planté" (segmentation fault, etc.)
	- sinon, détecte si le code de sortie renvoyé par l'<exécutable> correspond au code erreur attendu, donné dans le fichier .info
	- et détecte si la sortie de l'<executable> correspond à la sortie attendue, spécifiée dans le fichier .res

Enfin, le script génère un rapport de test avec les résultats de tous les tests.



########################################
#EXEMPLE DE FICHIER DE TEST
########################################


Voici un exemple de script de test, par exemple dans le fichier testaddition.scm :
	;———
	; TEST_RETURN_CODE=PASS		
  	; TEST_COMMENT="Test basic addition »	
  	;———
	(+ 5 4)
	(+ 5 -6)

Dans ce script de test, le mot clé PASS indique que ce test est censé passer sans erreur, c’est à dire que l’interpréter scheme
est censé renvoyer le code erreur 0 (zéro) lorsqu’il est lancé sur le test <test>.scm).

Ce script testaddition.scm doit être accompagné, dans le même répertoire, d’un fichier testadition.res, 
qui précise la sortie attendue du programme.
Dans notre cas, le script .res contiendra simplement le résultat de 5+4 puis de 5-6, c’est à dire :
   	==> 9
	==> -1
	

Enfin, pour exécuter ce test avec simpleUnitTest, on utilisera par exemple, dans le Terminal : 
	../testing/simpleUnitTest.sh -e ./scheme tests/testadition.scm


########################################
#EXEMPLE DE FICHIER DE TEST
########################################

Voici un exemple de script de test, par exemple dans le fichier testDetectionParentheseEnTrop.scm :
	;———
	; TEST_RETURN_CODE=FAIL		
  	; TEST_COMMENT=Teste qu’une parenthèse en trop est bien détectée	
  	;———
	(+ 5 9)
	(quote 5) )

Dans ce script de test, le mot clé FAIL indique que l’interpréter scheme est censé détecter
une erreur dans le script (la parenthèse en trop...) et générer une erreur, c’est à dire
arrêter le programme avec un code erreur non nul (par exemple avec la fonction C exit(1); ). 

Ce script testDetectionParentheseEnTrop.scm doit être accompagné, dans le même répertoire, d’un fichier testDetectionParentheseEnTrop.res, 
qui précise la sortie attendue du programme.
Dans notre cas, le script .res contiendra simplement le résultat de 5+4, c’est à dire :
   	==> 9
(puisque la seconde commande scheme (quote 5) ) provoque une erreur)	

Enfin, pour exécuter ce test avec simpleUnitTest, on utilisera par exemple, dans le Terminal : 
	../testing/simpleUnitTest.sh -e ./scheme tests/testDetectionParentheseEnTrop.scm



########################################
# Paramètres et options - en anglais
########################################


Exemple :
	$ ../testing/simpleUnitTest.sh -e ./scheme -o test_summary.txt tests/*.scm
	=> 	runs "../scheme" on all *scm files in the directory test
		and outputs results into test_summary.txt

	$ ../testing/simpleUnitTest.sh -e ./scheme -b -w tests/*.scm
	=> 	runs "../scheme" on all *scm files in the directory test
		quickly (-b option, « batch")
		and ignore all whitespace when checking program outputs (-w option, passed to diff, see man diff)
		

Usage: simpleUnitTest.sh -e <executablefile> [-b] [-p] [-d] [-q] [-v] [-o <summaryfile>] [-B] [-w] [-c] [-s <skip_file>] <args_testfiles>

simpleUnitTest.sh runs the <executablefile> specified in argument onto each of the test files specified in argument and checks the results

The employed <executablefile> is assumed to print its results onto stdout.
 
Each <testfile> in <args_testfiles> should contain, in comment:
   ; TEST_RETURN_CODE=X where X is in {PASS,FAIL,DO_NOT_CHECK}
and optionnaly :
   ; TEST_COMMENT=string that provides information about the test
 
Each test <testfile> in <args_testfiles> should be accompanied, in the same directory, with
  a file named <testfile>.res containing the expected standard output of the tested program for this <testfile>.
 
 The <executablefile> will be run on each <testfile> and :
	0/ store the standard output of <executablefile> in a file named <testfile>.out 
	1/ compare the return code value of the program with the expected return code value (PASS, ie 0, or FAIL, ie non 0)
	2/ generate a file <testfile>.out containing the output of the program (stdout of the tested program)
	3/ compare the expected output (<testfile>.res) with the standard output stdout of the tested program (<testfile>.out)
	4/ display results and generate a report

 Arguments :
	simpleUnitTest [-h] -e <executablefile> [options] <args_testfiles>
 Where :
	-e <executablefile> : name of the executable to test
 And 	
	args_testfiles	: list of test files on which to run the executable
 Options are :
	-h				: display help message
	-b				: batch mode : no user interaction
	-p				: pause mode : adds some delay in between two tests
	-d				: display debugs of tested program (display stderr of tested program)
	-q				: quiet mode : much less output while testing
	-v 				: verbose outputs (adds the test file and the out file)
	-c				: cleans the testing files before running :
							removes <summaryfile>
							removes any test output eg testfile.out
	-o <summaryFile>		: if used, writes the results into summaryfile
	-B				: if used, -B is passed to diff when comparing the results. See man diff
	-w				: if used, -w is passed to diff when comparing the results. See man diff
	-s <file>			: skip mode. Allows to interupt a test suite, then restart it later.
						Stores the ran test in <file> ; skip a test if already present in <file>.