export const examples = [
  {
    name: 'Prefix and Suffix',
    examples: [
      {
        message: 'New',
        prefix: 'Hello ',
        suffix: ' World',
        enable: {
          name: 'ps',
          display: 'Prefix and Suffix',
        },
        decoration: false,
      },
      {
        message: 'New',
        prefix: '${h} ',
        suffix: ' ${w}',
        enable: {
          name: 'ps',
          display: 'Prefix and Suffix',
        },
        decoration: false,
      },
      {
        message: 'act',
        prefix: 're',
        suffix: 'ive',
        enable: {
          name: 'ps',
          display: 'Prefix and Suffix',
        },
        decoration: false,
      },
      {
        message: 'act',
        prefix: 're',
        suffix: 'ive',
        enable: {
          name: 'p',
          display: 'Prefix',
        },
        decoration: false,
      },
      {
        message: 'act',
        prefix: 're',
        suffix: 'ive',
        enable: {
          name: 's',
          display: 'Suffix',
        },
        decoration: false,
      }
    ]
  },
  {
    name: 'Text Decoration',
    examples: [
      {
        message: 'Plane Text',
        enable: {
          name: 'n',
          display: 'None',
        },
        decoration: false,
      },
      {
        message: 'Red Text',
        enable: {
          name: 'n',
          display: 'None',
        },
        decoration: true,
        color: {
          name: 'red',
          display: 'Red',
        },
        bold: false,
        underline: false
      },
      {
        message: 'Green Text',
        enable: {
          name: 'n',
          display: 'None',
        },
        decoration: true,
        color: {
          name: 'green',
          display: 'Green',
        },
        bold: false,
        underline: false
      },
      {
        message: 'Blue Text',
        enable: {
          name: 'n',
          display: 'None',
        },
        decoration: true,
        color: {
          name: 'blue',
          display: 'Blue',
        },
        bold: false,
        underline: false
      },
      {
        message: 'Bold Text',
        enable: {
          name: 'n',
          display: 'None',
        },
        decoration: true,
        color: {
          name: 'white',
          display: 'White',
        },
        bold: true,
        underline: false
      },
      {
        message: 'Underline Text',
        enable: {
          name: 'n',
          display: 'None',
        },
        decoration: true,
        color: {
          name: 'white',
          display: 'White',
        },
        bold: false,
        underline: true,
      }
    ]
  }
]