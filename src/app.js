const { app } = require('electron')
const { BrowserWindow } = require('electron')

var mainWindow = null;

app.on('ready', function() {
    mainWindow = new BrowserWindow({
        width: 1024,
        height: 768
    })

    const mainHtml = getUrl('main/main.html')
    mainWindow.loadURL(mainHtml)
    mainWindow.openDevTools()
})

function getUrl(file) {
    return `file://${__dirname}/windows/${file}` 
}