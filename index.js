const SerialPort = require('serialport').SerialPort;
const { DelimiterParser } = require('@serialport/parser-delimiter')

const puerto = new SerialPort(
    {
        path:'COM4',
        baudRate: 9600
    }
);

const parser = puerto.pipe(new DelimiterParser({ delimiter: '\n'}))

parser.on('open',function () {
    console.log('Conexion abierta');
})

parser.on('data', function(data){
    var enc = new TextDecoder();
    var arr = new Uint8Array(data)
    ready = enc.decode(arr)
    console.log(ready);
})
puerto.on('error',function (err){
    console.log(err);
})