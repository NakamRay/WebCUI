<template>
  <v-dialog v-model="documentDialog" fullscreen persistent transition="dialog-bottom-transition">
    <v-card>
      <v-toolbar height="50px">
        <v-toolbar-title>Document</v-toolbar-title>
        
        <v-spacer></v-spacer>

        <v-btn icon @click="$store.commit('switchDocumentDialog')">
          <v-icon>mdi-close</v-icon>
        </v-btn>
      </v-toolbar>
      
      <v-tabs :vertical="$vuetify.breakpoint.smAndUp" color="dark">
        <v-tab>
          What's this?
        </v-tab>
        <v-tab>
          Features
        </v-tab>

        <v-tab-item>
          <v-card flat style="overflow-y: auto;" :height='windowHeight'>

            <v-card-title>What's this?</v-card-title>
            <v-card-text>
              <p>
                This is a sample program of "CUI to WUI". It is a framework for implementing the web user interface of your CUI application.
              </p>
            </v-card-text>
            
          </v-card>
        </v-tab-item>
        <v-tab-item>
          <v-card flat style="overflow-y: auto;" :height='windowHeight'>

            <v-card-title>画面</v-card-title>
            <v-card-text>
              <p>
                画面右にある3つのアイコン（縦長の画面では右下の青いボタンを押すと表示される）は，クリックすると以下の処理を実行します．
              </p>
              <div class="py-2"></div>
              <div class="mb-2"><v-icon>mdi-delete</v-icon> <b>コンソールのクリア</b></div>
              <p>
                コンソールの内容を消去します．
                消去された内容は「<v-icon>mdi-history</v-icon> <b>コンソール履歴の表示</b>」に保持されます．
              </p>
              <div class="mb-2"><v-icon>mdi-history</v-icon> <b>コンソール履歴の表示</b></div>
              <p>
                クリアされたコンソールの内容が蓄積された履歴を表示します．
              </p>
              <div class="mb-2"><v-icon>mdi-alpha-e-box</v-icon> <b>例の表示</b></div>
              <p>
                パラメータの入力例を一覧します．クリックすることでそのパラメータがセットされます．
              </p>
              <div class="mb-2"><v-icon>mdi-order-alphabetical-ascending</v-icon> <b>変数の管理</b></div>
              <p>
                変数の定義・確認・更新・削除ができます．ここで定義された変数は，パラメータの入力フォーム内で使うことが出来ます．
                例えば<code>h = Hello</code>と変数が定義されている場合，入力フォームに<code>${h} World!</code>と入力すると，パラメータとして<code>Hello World!</code>が送信されます．
              </p>
              <div class="mb-2"><v-icon>mdi-play</v-icon> <b>APIリクエストの送信</b></div>
              <p>
                セットされているパラメータが指定されたWebAPIに送信されます．
              </p>
            </v-card-text>

          </v-card>
        </v-tab-item>
      </v-tabs>
    </v-card>
  </v-dialog>
</template>

<script>
import { mapState } from "vuex";

export default {
  data: () => ({
    windowHeight: 0
  }),
  computed: {
    ...mapState(["documentDialog"]),
  },
  methods: {
    updateDialogHeight () {
      var tabsHeight = this.$vuetify.breakpoint.smAndUp ? 0 : 48
      this.windowHeight = window.innerHeight - tabsHeight - 50
    }
  },
  mounted () {
    this.updateDialogHeight()
    window.addEventListener('resize', this.updateDialogHeight)
  }
}
</script>

<style scoped src="~/assets/styles.css"/>
