export const params = {
  file: {
    display: 'File',
    type: 'file',
    target: 'rs',
    default: [],
    size: 'whole'
  },
  form: {
    display: 'Format',
    type: 'select',
    items: [
      {
        name: 'hs',
        display: 'SOL (.hs)',
      },
      {
        name: 'trs',
        display: 'TRS',
      },
      {
        name: 'haskell',
        display: 'GHC Rules'
      }
    ],
    default: {
      name: 'hs',
      display: 'SOL (.hs)',
    },
    size: 'half'
  },
  pro: {
    display: 'Check',
    type: 'select',
    items: [
      {
        name: 'cr',
        display: 'CR',
      },
      {
        name: 'cr_CBV',
        display: 'CR(CBV)',
      },
      {
        name: 'snG',
        display: 'SN'
      },
      {
        name: 'cri',
        display: 'WCR'
      },
    ],
    default: {
      name: 'cr',
      display: 'CR',
    },
    size: 'half'
  },
  rs: {
    display: 'File body',
    type: 'textarea',
    rows: 18,
    default: '',
    size: 'whole'
  }
}
