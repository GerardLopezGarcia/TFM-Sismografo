const { SerialPort } = require('serialport');
const Readline = require('@serialport/parser-readline');
//DEPRECATED----------------------------------- NO USAR
const puertoSerial = 'COM4'; // Cambia esto al nombre de tu puerto COM

const puerto = new SerialPort({
path: 'COM4',
baudRate: 19200,
dataBits: 8,
stopBits: 1,
parity: 'none',

});

const parser = Readline
puerto.pipe(parser);

puerto.on('open', () => {
  console.log(`Conexión establecida con ${puertoSerial}.`);
});

parser.on('data', (line) => {
  console.log(`Datos recibidos: ${line}`);
});

puerto.on('error', (err) => {
  console.error('Error en el puerto serial:', err);
});
