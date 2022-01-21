# About
This is a C program that consists in a series of filters for WAV audio files.  
It was developed as an assingment for the Programming II (CI1002) course of the Federal University of Paraná (UFPR).

# Data Structure used
The main data structure used in this project is called <code>t_wav</code>, which is defined in <code>wav.h</code> file, and it represents the WAV file.

# How to use the program
## Compiling
To compile the program, execute the following command inside the project directory:
```bash
$ make
```
After that, several executable files will be ready to use.

## Executable files
Each executable file is a different filter, with the exception of <code>wavinfo</code>.

### WavInfo
Shows info about the input WAV file.
```bash
$ wavinfo -i input
```
<code>-i</code> indicates the input file. If it is not used, the input will be read from <code>stdin</code>.

### WavVol
Adjusts the audio volume, according to an input value V (0.0 ≤ V ≤ 10.0).
```bash
$ wavvol -i input -l V -o output
```
<code>-i</code> indicates the input file. If it is not used, the input will be read from <code>stdin</code>.  
<code>-l</code> indicates the audio volume adjust factor. If it is not used, the default value will be 1.  
<code>-o</code> indicates the output file. If it is not used, the program will use <code>stdout</code> as its output.

### WavNorm
Normalizes the audio file.
```bash
$ wavnorm -i input -o output
```
<code>-i</code> indicates the input file. If it is not used, the input will be read from <code>stdin</code>.  
<code>-o</code> indicates the output file. If it is not used, the program will use <code>stdout</code> as its output.

### WavRev
Reverses the audio file.
```bash
$ wavnorm -i input -o output
```
<code>-i</code> indicates the input file. If it is not used, the input will be read from <code>stdin</code>.  
<code>-o</code> indicates the output file. If it is not used, the program will use <code>stdout</code> as its output.

### WavEcho
This filter produces echo on the audio. It is controlled by 2 parameters: *delay* (0 < delay, in ms) and *level* (0.0 ≤ level ≤ 1.0).
```bash
$ wavecho -i input -t delay -l level -o output
```
<code>-i</code> indicates the input file. If it is not used, the input will be read from <code>stdin</code>.  
<code>-t</code> indicates the delay. If it is not used, the default value will be 1000ms.  
<code>-l</code> indicates the echo level. If it is not used, the default value will be 0.5.  
<code>-o</code> indicates the output file. If it is not used, the program will use <code>stdout</code> as its output.

### WavWide
This filter amplifies the separation between two channels, according to a parameter *k* (0.0 ≤ k ≤ 10.0). It only works on **stereo** audio files.
```bash
$ wavwide -i input -l k -o output
```
<code>-i</code> indicates the input file. If it is not used, the input will be read from <code>stdin</code>.  
<code>-l</code> indicates the k parameter. If it is not used, the default value will be 1.  
<code>-o</code> indicates the output file. If it is not used, the program will use <code>stdout</code> as its output.

### WavCat
This filter concatenates different audio files. They must have the **same number of channels**.
```bash
$ wavcat file1.wav file2.wav file3.wav ... -o output
```
The file names **must** be indicated when executing this filter.
<code>-o</code> indicates the output file. If it is not used, the program will use <code>stdout</code> as its output.

### WavMix
This filter mixes different different audio files. They must have the **same number of channels**.
```bash
$ wavmix file1.wav file2.wav file3.wav ... -o output
```
The file names **must** be indicated when executing this filter.
<code>-o</code> indicates the output file. If it is not used, the program will use <code>stdout</code> as its output.

#Usage example
```bash
$ ./wavrev -i input.wav | ./wavecho -t 425 -l 0.6 | ./wavrev -o output.wav
```

# Authors
This project was developed by [@leonokida](https://github.com/leonokida).
