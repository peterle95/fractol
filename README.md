# fract-ol

<p align="center">
  <img src="https://github.com/mcombeau/mcombeau/blob/main/42_badges/fract-ole.png" alt="Fract'ol fract-ol 42 project badge"/>
</p>

One of the first graphical projects at 42 school, fract-ol generates beautiful fractals from the complex numbers of an iterative mathematical construct. A fractal is a fragmented geometrical figure that infinitely repeats itself at smaller scales. This project uses the school's graphical library, MiniLibX.

![Fract-ol orange and yellow striped Mandelbrot](https://github.com/peterle95/fractol/blob/main/screenshots/Mandelbrot%201.png)

# Usage

## Installing and Compiling Fract-ol

Clone the repository, including the MiniLibX repository:
```shell
git clone https://github.com/peterle95/fractol.git && cd fract-ol
```

You will now be in the correct directory for compilation. Compile with `make`. Fract-ol should now be ready!

## Executing Fract-ol

At execution time, you must specify a fractal to display. You may also provide other optional parameters:

```shell
./fractol <type> <options>
```

Types are :
* ```1```, ```2```, ```3```, or ```4```: Mandelbrot fractal (Different color schemes)
* ```5```, ```6```, ```7```, or ```8```: Julia fractal (Different color schemes)


For the Julia fractal set (and only this set), two additional parameters can be specified as calculation values. These represent a complex number that will change the shape of the Julia fractal. They must be fractional numbers between 2.0 and -2.0. For example:

```shell
./fractol julia 0.285 -0.01
```

## Fract-ol Controls

While Fractol is running, the following set of controls are available:

<table>
  <tr><td><strong>Controls</strong></td><td><strong>Action</strong></td></tr>
  <tr><td><kbd>&nbsp;▲&nbsp;</kbd><kbd>&nbsp;◄&nbsp;</kbd><kbd>&nbsp;▼&nbsp;</kbd><kbd>&nbsp;►&nbsp;</kbd></td><td>Move</td></tr>
  <tr><td><kbd>&nbsp;scroll wheel&nbsp;</kbd></td><td>Zoom in and out</td></tr>
  <tr><td><kbd>&nbsp;1&nbsp;</kbd>, <kbd>&nbsp;2&nbsp;</kbd>, <kbd>&nbsp;3&nbsp;</kbd>, <kbd>&nbsp;4&nbsp;</kbd>, <kbd>&nbsp;5&nbsp;</kbd>, <kbd>&nbsp;6&nbsp;</kbd>, <kbd>&nbsp;7&nbsp;</kbd>, <kbd>&nbsp;8&nbsp;</kbd></td><td>Switch fractals</td></tr>
  <tr><td><kbd>&nbsp;esc&nbsp;</kbd> or close window</td><td>Quit fract-ol</td></tr>
</table>

# Screenshots

## Mandelbrot set

![Fract-ol black, blue and green striped Mandelbrot](https://github.com/peterle95/fractol/blob/main/screenshots/Mandelbrot%202.png)

## Julia set

![Fract-ol purple orange and yellow striped Julia](https://github.com/peterle95/fractol/blob/main/screenshots/Julia%201.png)
![Fract-ol black, blue and green striped Julia](https://github.com/peterle95/fractol/blob/main/screenshots/Julia%202.png)

---
Made by pmolzer: pmolzer@student.42berlin.de | LinkedIn: [pmolzer](https://www.linkedin.com/in/peter-moelzer//) 
