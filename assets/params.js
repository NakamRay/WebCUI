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
  text: {
    display: 'Text',
    type: 'text',
    default: '',
    size: 'whole', // can be omitted.
    required: true // This param will be a required param. 'required' can be set when 'type' is 'text'.
  }
}
