# The Puppet
<!--
[![GitHub issues](https://img.shields.io/github/issues/JacobHdez/The-Puppet?style=for-the-badge)](https://github.com/JacobHdez/The-Puppet/issues)
[![GitHub forks](https://img.shields.io/github/forks/JacobHdez/The-Puppet?style=for-the-badge)](https://github.com/JacobHdez/The-Puppet/network)
[![GitHub stars](https://img.shields.io/github/stars/JacobHdez/The-Puppet?style=for-the-badge)](https://github.com/JacobHdez/The-Puppet/stargazers)
[![GitHub license](https://img.shields.io/github/license/JacobHdez/The-Puppet?style=for-the-badge)](https://github.com/JacobHdez/The-Puppet) <br>
-->
![GitHub last commit](https://img.shields.io/github/last-commit/JacobHdez/The-Puppet?style=for-the-badge)
![GitHub repo size](https://img.shields.io/github/repo-size/JacobHdez/The-Puppet?style=for-the-badge)

![The Puppet](./images/The_Puppet.png)

## Description

Para esta tarea se implement� una c�mara de perspectiva que se controla con WASD

- W: Arriba
- S: Abajo
- A: Izquierda
- D: Derecha

Adem�s, se puede rotar la c�mara sobre su mismo eje al mover el rat�n mientras se hace clic con el boton derecho del rat�n.

La marioneta fue dise�ada a partir de un modelo jer�rquico, donde cada extremidad esta dise�ada por una esfera, donde se le aplicaron sus correspondientes transformaciones para formar a esta.

Se cuenta con una interfaz b�sica echa con [ImGui](https://github.com/ocornut/imgui), para poder controlar a la marioneta. El torso se puede rotar como trasladar, mientras que las dem�s extremidades solamente se pueden rotar. No se implemento un l�mite para las rotaciones para que no se hagan movimientos �extra�os�.
![Vista General](./images/Controls.gif)


Tambi�n se cuenta con un sistema b�sico de iluminaci�n que cuenta con una �nica luz representada por un cubo.
![Iluminaci�n](./images/Lighting.gif)


As� como un bot�n para reiniciar la marioneta a su configuraci�n inicial.
![Reiniciar Marioneta](./images/Reset.gif)


Se aplico la prueba de profundidad a partir de las funciones que ya cuenta OpenGl.


## Fuentes

- [The Cherno - OpenGL Series](https://www.youtube.com/playlist?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2)
- [Learn OpenGL](https://learnopengl.com)
- [OpenGl - Tutorial](http://www.opengl-tutorial.org/es/)