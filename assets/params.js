// The 'type' can be set to 'text', 'select', 'autocomplete', 'switch', 'file', 'textarea' or 'invisible'.
/* 
If you want to show the contents of the file, please set a 'target' key in the 'file' type object.
For example,
  file: {
    display: 'File',
    type: 'file',
    target: 'fileBody',
    default: [],
    size: 'whole'
  },
  fileBody: {
    display: 'File body',
    type: 'textarea',
    rows: 5,
    default: '',
    size: 'whole'
  }
*/
// The 'size' can be set to 'whole', 'half' or 'quarter'.
export const params = {
  message: {
    display: 'Message',
    type: 'text',
    default: '',
    size: 'whole', // can be omitted.
    required: true // This param will be a required param. 'required' can be set when 'type' is 'text'.
  },
  prefix: {
    display: 'Prefix',
    type: 'text',
    default: '',
    size: 'quarter'
  },
  suffix: {
    display: 'Suffix',
    type: 'text',
    default: '',
    size: 'quarter'
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
      {
        name: 'n',
        display: 'None'
      },
    ],
    default: {
      name: 'ps',
      display: 'Prefix and Suffix',
    },
    size: 'half'
  },
  decoration: {
    display: 'Text Decoration',
    type: 'switch',
    default: true,
    size: 'quarter'
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
    size: 'quarter'
  },
  bold: {
    display: 'Bold',
    type: 'check',
    default: false,
    size: 'quarter'
  },
  underline: {
    display: 'Underline',
    type: 'check',
    default: false,
    size: 'quarter'
  }
}
