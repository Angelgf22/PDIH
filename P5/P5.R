library(tuneR)
library(seewave)
library(audio)

# Añadimos los archivos de audio

Nombre <- readWave('nombre.wav')
Apellidos <- readWave('apellidos.wav')

# Calculamos la duración
round(length(Nombre@left) / Nombre@samp.rate, 3)

# Mostrar forma de onda hasta el final (usamos duración para la ultima muestra)
plot(extractWave(Nombre, from = 1, to = 1873000))

# Calculamos la duración
round(length(Apellidos@left) / Apellidos@samp.rate, 3)

# Mostrar forma de onda hasta el final
plot(extractWave(Apellidos, from = 1, to = 1345000))

# Cabecera audio Nombre
Nombre

# Cabecera audio Apellidos
Apellidos

# Unimos nombre y apellidos

NombreApellidos <- pastew(Apellidos, Nombre , output="Wave")

# Forma de onda resultante

round(length(NombreApellidos@left) / NombreApellidos@samp.rate, 3)
plot(extractWave(NombreApellidos, from = 1, to = 3218000))

# Eliminamos las frecuencias entre 10000Hz y 20000Hz
NombreApellidosFiltrado <- bwfilter(NombreApellidos, 48000, channel = 1, n = 1, from =  10000,
                    to = 20000, bandpass = TRUE, listen = FALSE, output = "Wave")

# Visualizmos la forma de onda
plot(extractWave(NombreApellidosFiltrado, from = 1, to = 3218000))

# Guardamos el resultado como mezcla.wav
writeWave(NombreApellidosFiltrado, file.path("mezcla.wav"))

# Añadimos nuevo audio
nuevoAudio <- readWave('nombreapellidos.wav')

# Añadimo eco:

nuevoAudioEco <- echo(nuevoAudio,f=22050,amp=c(0.8,0.4,0.2),delay=c(1,2,3),
                output="Wave")
nuevoAudioEco@left <- 10000 * nuevoAudioEco@left


# Al reves:
nuevoAudioEcoAlreves <- revw(nuevoAudioEco, output="Wave")

# Visualizamos la forma de onda
#plot(extractWave(nuevoAudioAlreves, from = 1, to = 3218000))

# Guardamos
writeWave(nuevoAudioEcoAlreves, file.path("alreves.wav"))









