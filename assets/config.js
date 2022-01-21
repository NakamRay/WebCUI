export const config = {
  name: `GSOL`,                // Application's name

  // logo: `logo_icon.png`,        // A filename in ~/static/

  address: '/webcui/gsol',      // http://localhost:3000/[address]

  webApiUrl: `http://solweb.mydns.jp/webcui/gsol/api/api.php`,

  consoleLocation: 'right',    // Placing the console. [left | right | top | bottom]
  toolbarLocation: 'left',    // Placing the toolbar. [left | right]
  
  keepState: false,

  messages: {
    initialMsg: [{ text: `Please refer to the DOCUMENT on the upper right of this page for the instructions.` }],
    connectionErrorMsg: [{ text: `An error occurred while communicating with the server.` }],
    cancelRequestMsg: [{ text: `Canceled by the user.` }],
    readErrorMsg: [{ text: `An error occured while reading the file.` }]
  },

  features: {
    clear: {
      enable: true,
      icon: 'mdi-delete',
      text: 'Clear'
    },
    history: {
      enable: false,
      icon: 'mdi-history'
    },
    examples: {
      enable: false,
      icon: 'mdi-alpha-e-box'
    },
    files: {
      enable: true,
      icon: 'mdi-file-multiple',
      text: 'Examples',
      webApiUrl: 'http://solweb.mydns.jp/webcui/gsol/api/files.php',
    },
    variables: {
      enable: false,
      icon: 'mdi-order-alphabetical-ascending'
    },
    sendReq: {
      enable: true,
      icon: 'mdi-play',
      text: 'Check',
      before: (webcui) => {
        webcui.clearConsole()
      },
      after: (webcui, result) => {
        webcui.addLine({ html: result })
      }
    }
  }
}

// export const config = {
//   name: `GSOL`,                // Application's name

//   // logo: `logo_icon.png`,        // A filename in ~/static/

//   webApiUrl: `http://solweb.mydns.jp/webcui/gsol/api/api.php`,

//   consoleLocation: 'right',    // Placing the console. [left | right | top | bottom]
//   toolbarLocation: 'left',    // Placing the toolbar. [left | right]
  
//   keepState: false,

//   messages: {
//     initialMsg: [{ text: `Please refer to the DOCUMENT on the upper right of this page for the instructions.` }],
//     connectionErrorMsg: [{ text: `An error occurred while communicating with the server.` }],
//     cancelRequestMsg: [{ text: `Canceled by the user.` }],
//     readErrorMsg: [{ text: `An error occured while reading the file.` }]
//   },

//   features: {
//     clear: {
//       enable: true,
//       icon: 'mdi-delete',
//       text: 'Clear'
//     },
//     history: {
//       enable: false,
//       icon: 'mdi-history'
//     },
//     examples: {
//       enable: false,
//       icon: 'mdi-alpha-e-box'
//     },
//     files: {
//       enable: true,
//       icon: 'mdi-file-multiple',
//       text: 'Examples',
//       webApiUrl: 'http://solweb.mydns.jp/webcui/gsol/api/files.php',
//     },
//     variables: {
//       enable: false,
//       icon: 'mdi-order-alphabetical-ascending'
//     },
//     sendReq: {
//       enable: true,
//       icon: 'mdi-play',
//       text: 'Check',
//       before: (webcui) => {
//         webcui.clearConsole()
//       },
//       after: (webcui, result) => {
//         webcui.addLine({ html: result })
//       }
//     }
//   }
// }
