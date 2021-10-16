const optionItems = [
  {
    name: 'register',
    display: 'アカウント作成',
  },
  {
    name: 'start',
    display: '近い会議の開始',
  },
  {
    name: 'make',
    display: '会議の作成',
    flag: 'meeting'
  },
  {
    name: 'list',
    display: '会議の一覧',
  },
  {
    name: 'edit',
    display: '会議の編集',
    flag: 'meeting'
  },
  {
    name: 'delete',
    display: '会議の削除',
    flag: 'meeting'
  }
]

const day = [
  {
    name: 'Monday',
    display: '月'
  },
  {
    name: 'Tuesday',
    display: '火'
  },
  {
    name: 'Wednesday',
    display: '水'
  },
  {
    name: 'Thursday',
    display: '木'
  },
  {
    name: 'Friday',
    display: '金'
  },
  {
    name: 'Saturday',
    display: '土'
  },
  {
    name: 'Sunday',
    display: '日'
  }
]  

export const params = {
  user: {
    display: 'ユーザ名',
    type: 'text',
    default: ''
  },
  option: {
    display: '',
    type: 'select',
    items: optionItems,
    default: optionItems[0]
  },
  name: {
    display: '会議名',
    type: 'text',
    default: '',
    if: 'meeting'
  },
  url: {
    display: '会議URL',
    type: 'text',
    default: '',
    if: 'meeting'
  },
  weekly: {
    display: '毎週の予定',
    type: 'check',
    default: false,
    size: 'half',
    if: 'meeting',
    flag: 'weekly'
  },
  day: {
    display: '曜日',
    type: 'select',
    items: day,
    default: day[0],
    size: 'half',
    if: 'weekly'
  },
  year: {
    display: '年',
    type: 'select',
    items: [
      ...[...Array(5)].map((_, i) => {
        return { name: String(21 + i), display: String(2021 + i) }
      })
    ],
    default: { name: '21', display: '2021'},
    size: 'half',
    if: 'meeting'
  },
  date: {
    display: '月日',
    type: 'text',
    default: '0101',
    size: 'half',
    if: 'meeting'
  },
  shour: {
    display: '開始時',
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
    size: 'quarter',
    if: 'meeting'
  },
  sminute: {
    display: '開始分',
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
    size: 'quarter',
    if: 'meeting'
  },
  ehour: {
    display: '終了時',
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
    size: 'quarter',
    if: 'meeting'
  },
  eminute: {
    display: '終了分',
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
    size: 'quarter',
    if: 'meeting'
  }
}
