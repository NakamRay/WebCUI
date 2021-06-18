// The type can be set to 'text', 'select' or 'switch'.
export const params = {
  message: {
    display: 'Message',
    type: 'text',
    default: '',
    size: 'whole', // can be omitted.
    visible: true
  },
  prefix: {
    display: 'Prefix',
    type: 'text',
    default: '',
    size: 'quarter',
    visible: true
  },
  suffix: {
    display: 'Suffix',
    type: 'text',
    default: '',
    size: 'quarter',
    visible: true
  },
  enable: {
    display: 'Enable',
    type: 'select',
    items: [
      {
        name: 'ps',
        display: 'Prefix and Suffix',
      },
      {
        name: 'p',
        display: 'Prefix only',
      },
      {
        name: 's',
        display: 'Suffix only'
      },
    ],
    default: {
      name: 'ps',
      display: 'Prefix and Suffix',
    },
    size: 'half',
    visible: true
  },
  decoration: {
    display: 'Text Decoration',
    type: 'switch',
    default: true,
    size: 'quarter',
    visible: true
  },
  color: {
    display: 'Color',
    type: 'select',
    items: [
      {
        name: 'white',
        display: 'White',
      },
      {
        name: 'red',
        display: 'Red',
      },
      {
        name: 'green',
        display: 'Green',
      },
      {
        name: 'blue',
        display: 'Blue'
      },
    ],
    default: {
      name: 'white',
      display: 'White',
    },
    size: 'quarter',
    visible: true
  },
  bold: {
    display: 'Bold',
    type: 'check',
    default: false,
    size: 'quarter',
    visible: true
  },
  underline: {
    display: 'Underline',
    type: 'check',
    default: false,
    size: 'quarter',
    visible: true
  },
}
