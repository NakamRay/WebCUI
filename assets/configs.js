export const appInfo = {
  name: 'CUI to WUI',
  baseUrl: "http://localhost/",
  apiFile: "sample-api.php"
}

export const logo = {
  // icon: require('~/static/logo_icon.png'),
  // text: require('~/static/logo_text.png')
}

export const messages = {
  initialMessage: '使用方法は画面右上のDOCUMENTを参照してください．',
  connectionErrorMessage: 'An error occurred while communicating with the server.',
}

// type can be set to 'text' or 'select'
export const params = {
  message: {
    display: 'A message to send to API',
    type   : 'text',
    default: '',
    visible: true
  }
}
