/*
You can set multiple categories of the examples like:
examples = [
  { name: 'A', examples: [...some examples] },
  { name: 'B', examples: [...some examples] },
  ...
]

In 'examples', the parameter keys set in 'params.js' must be used.
*/
export const examples = [
  {
    display: 'Prefix and Suffix',
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
    display: 'Text Decoration',
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
