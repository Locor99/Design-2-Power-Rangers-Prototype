**Auteur: Louis Cormier**

# Pour cloner
Vous pouvez utiliser Github Desktop, SourceTree ou autres.
Si vous utilisez CLion comme IDE, le client Git est sur la coche.

# IDE
À la place du Arduino IDE, d'autres options sont possibles:

Pour utiliser CLion et le plugin PlatformIO pour le Ardudino, voir la documentation:
https://www.jetbrains.com/help/clion/platformio.html
Il est aussi possible d'utiliser un plugin sur VSCode.

# Unit tests
## Lancer les tests
Pour rouler les tests, il faut tout d'abord installer gnu gcc compiler.
https://www.codewithharry.com/blogpost/how-to-install-gnu-gcc-compiler-on-windows/

Ensuite, dans la console, il faut faire:
```pio test -e native```

## Écrire des tests
Pour mocker le hardware Arduino, se référer à https://registry.platformio.org/libraries/fabiobatsilva/ArduinoFake

Voir cette page pour organiser les tests: https://docs.platformio.org/en/latest/advanced/unit-testing/structure/hierarchy.html

Il y a des points importants à comprendre sur comment les tests sont exécutés pour bien organiser les fichiers (c'est 1 projet par dossier test donc un main par dossier test)