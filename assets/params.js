export const params = {
  xi: {
    display: 'Type Context',
    type: 'text',
    default: '',
    size: 'half'
  },
  ga: {
    display: 'Term Context',
    type: 'text',
    default: '',
    size: 'half'
  },
  term: {
    display: 'Lambda Term',
    type: 'text',
    default: '',
    size: '10',
    required: true
  },
  isUntyped: {
    display: 'Untyped',
    type: 'switch',
    default: false,
    size: '2'
  },
  mode: {
    default: 'init'
  },
  num: {
    default: ''
  },
  newTerm: {
    default: ''
  }
}
