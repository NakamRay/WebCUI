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
  type: {
    display: 'Type',
    type: 'select',
    items: [
      {
        name: 'rect',
        display: 'Rectangle',
        flag: 'rect'
      },
      {
        name: 'circle',
        display: 'Circle',
        flag: 'circle'
      }
    ],
    default: {
      name: 'rect',
      display: 'Rectangle',
      flag: 'rect'
    },
    size: 'whole',
  },
  base: {
    display: 'Base',
    type: 'text',
    default: '',
    size: 'half',
    if: 'rect'
  },
  height: {
    display: 'Height',
    type: 'text',
    default: '',
    size: 'half',
    if: 'rect'
  },
  radius: {
    display: 'Radius',
    type: 'text',
    default: '',
    size: 'whole',
    if: 'circle'
  },
  setPi: {
    display: 'Set π',
    type: 'check',
    default: false,
    size: 'half',
    flag: 'test',
    if: 'circle'
  },
  pi: {
    display: 'π',
    type: 'text',
    default: '3.14',
    size: 'half',
    if: 'test'
  }
}
