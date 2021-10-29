import { stations } from '@/static/stations.js'

export const params = {
  from: {
    display: 'From',
    type: 'select',
    items: stations,
    default: '高崎',
    size: 'half'
  },
  to: {
    display: 'To',
    type: 'select',
    items: stations,
    default: '前橋',
    size: 'half'
  }
}
