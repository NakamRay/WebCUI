export const examples = {
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
      message: 'New',
      prefix: 'Hello ',
      suffix: ' World',
      enable: {
        name: 'ps',
        display: 'Prefix and Suffix',
      },
    },
    {
      message: 'New',
      prefix: '${h} ',
      suffix: ' ${w}',
      enable: {
        name: 'ps',
        display: 'Prefix and Suffix',
      },
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
    },
    {
      message: 'Bold Text',
      enable: {
        name: 'n',
        display: 'None',
      },
      decoration: true,
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
      bold: false,
      underline: true,
    }
  ]
}
