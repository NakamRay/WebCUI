export const name = "CLI to WUI"

export const logo = {
  // icon: require('~/static/logo_icon.png'),
  // text: require('~/static/logo_text.png')
}

export const messages = {
  initialMessage: "使用方法は画面右上のUsageを参照してください．",
  connectionErrorMessage: "サーバとの通信中にエラーが発生しました．",
}

export const params = {
  message: {
    display: 'A message to send to API',
    type: String,
    default: null,
    value: null,
    visible: true
  },
  message1: {
    display: 'A message to send to API',
    type: String,
    default: null,
    value: null,
    visible: true
  }
}
