export const params = {
  prop: {
    display: 'Check command',
    type: 'select',
    items: ['cri','sn','cr'],
    default: 'cri',
  },
  s: {
    display: 'Dump SOL Rules',
    type: 'check',
    default: false,
    size: 4
  },
  r: {
    display: 'Dump GHC Core Rules',
    type: 'check',
    default: false,
    size: 4
  },
  t: {
    display: 'Dump the signature for GHC Core Rules',
    type: 'check',
    default: false,
    size: 4
  },
  n: {
    display: 'Print number of GHC Core Rules',
    type: 'check',
    default: false,
    size: 4
  },
  p: {
    display: 'Dump GHC Core program and types',
    type: 'check',
    default: false,
    size: 4
  },
  phases: {
    display: 'Whether to do phase splitting',
    type: 'check',
    default: false,
    size: 4
  },
  hs: {
    display: 'Haskell Program',
    type: 'textarea',
    rows: 15,
    default: ''
  }
}
