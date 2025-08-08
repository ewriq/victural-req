const { SerialPort } = require('serialport');

const PORT_PATH = 'COM3';
const BAUD_RATE = 500000;

console.log(`Connecting to port '${PORT_PATH}' at baud rate ${BAUD_RATE}...`);

const port = new SerialPort({
  path: PORT_PATH,
  baudRate: BAUD_RATE,
  dataBits: 8,
  parity: 'none',
  stopBits: 1,
  rtscts: true,
});


let receiveBuffer = '';
const delimiter = '\n';

port.on('data', (chunk) => {
  receiveBuffer += chunk.toString();

  let delimiterIndex;
  while ((delimiterIndex = receiveBuffer.indexOf(delimiter)) >= 0) {
    const line = receiveBuffer.slice(0, delimiterIndex).trim();

    receiveBuffer = receiveBuffer.slice(delimiterIndex + 1);

    if (line.length > 0) {
      handleLine(line);
    }
  }
});

function handleLine(line) {
  try {
    if (line.startsWith('{') && line.endsWith('}')) {
      const jsonData = JSON.parse(line);
      console.log('PARSED JSON:', jsonData);
    }
  } catch (e) {
    console.error('JSON parse error on line:', line, 'Error:', e.message);
  }
}


port.on('open', () => {
  console.log('----------------------------------------------------');
  console.log(' SUCCESS: Port opened. Using Robust Manual Buffer.');
  console.log('----------------------------------------------------');

  const dataToSend = process.argv[2];
  if (dataToSend) {
    port.write(dataToSend + '\n', (err) => {
      if (err) {
        return console.error('Failed to send command. Error:', err.message);
      }
      console.log(`COMMAND SEND: ${dataToSend}`);

    });
  } else {
    process.exit(0);
  }
});

port.on('error', (err) => {
  console.error('>>> KİRİTİK PORT ERROR:', err.message);
});

port.on('close', () => {
  console.log('Port closed.');
});