export const config = {
  name: `WUI for CUI Sample`, // Your application's name
  /*
    If you want to use logo images of your application, set it to 'logo'.
    Images you set to 'icon' and 'text' will be lined up next to each other on the top of the page.
    If the appearance is broken, please adjust the height and width of the image in '~/layouts/default.vue'.
    If you don't use the icon image, you cant omit 'icon'.
    If you omit 'text', your application's name will be displayed instead of the text logo.
  */
  logo: {
    icon: `logo_icon.png`,      // Filename in ~/static/
    // text: `logo_text.png`,   // This is needed if you want to use a text logo.
  },

  baseUrl: `http://localhost/`,  // If you want to use multiple APIs,
  apiFileName: `sample-api.php`, // code them in '~/pages/index.vue'.

  messages = {
    initialMsg: [{ text: `Please refer to the DOCUMENT on the upper right of this page for the instructions.` }],
    connectionErrorMsg: [{ text: `An error occurred while communicating with the server.` }]
  },

  swapLayouts: false             // Swap forms and the console.
}
