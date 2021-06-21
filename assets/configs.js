export const appInfo = {
  name: 'CUI to WUI Sample',
  baseUrl: 'http://localhost/',  // If you want to use multiple APIs,
  apiFileName: 'sample-api.php', // code them in '~/pages/index.vue'.
  htmlConsole: true,             // HTML tag will be enabled in the console.
  swapLayouts: false             // swap forms and the console.
}

/*
If you want to use a icon of your application, set it here.
Images of 'icon' and A 'text' are lined up next to each other.
If the appearance is broken, adjust the height and width of the image in '~/layouts/default.vue'.
If you omit the 'text', only the icon will be displayed at the top of the page.
*/
export const logo = {
  // icon: require('~/static/logo_icon.png'),
  // text: require('~/static/logo_text.png')
}

// 'initialMessage' is initially displayed on the console.
export const messages = {
  initialMessage: [{ text: 'Please refer to the DOCUMENT on the upper right of this page for instructions.' }],
  connectionErrorMessage: [{ text: 'An error occurred while communicating with the server.' }]
}
