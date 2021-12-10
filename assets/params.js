import { stations } from '@/static/stations.js'

export const params = {
  from: {
    display: 'From',
    type: 'select',
    items: stations,
    default: '高崎',
    size: 'quarter'
  },
  to: {
    display: 'To',
    type: 'select',
    items: stations,
    default: '前橋',
    size: 'quarter'
  },
  hour: {
    display: '時',
    type: 'autocomplete',
    items: [
      ...[...Array(24)].map((_, i) => {
        return { name: i < 10 ? '0' + i : i, display: i }
      })
    ],
    default: {
      name: '00',
      display: '0'
    },
    size: 'quarter'
  },
  minute: {
    display: '分',
    type: 'autocomplete',
    items: [
      ...[...Array(60)].map((_, i) => {
        return { name: i < 10 ? '0' + i : i, display: i }
      })
    ],
    default: {
      name: '00',
      display: '0'
    },
    size: 'quarter'
  }
}
