<template>
  <div>
    <h3>Toolbar</h3>
      <p>
        画面右にあるToolbar（縦長の画面では右下の青いボタンを押すと表示される）は，各アイコンをクリックすると以下の処理を実行します．
      </p>

      <br>

      <h4 class="mb-2"><v-icon class="mr-3">mdi-delete</v-icon><b>コンソールのクリア</b></h4>
      <p>
        コンソールの内容を消去します．
        消去された内容はコンソール履歴に蓄積されます．
      </p>
      <h4 class="mb-2"><v-icon class="mr-3">mdi-history</v-icon><b>コンソール履歴の表示</b></h4>
      <p>
        クリアされたコンソールの内容が蓄積された履歴を表示します．
      </p>
      <h4 class="mb-2"><v-icon class="mr-3">mdi-alpha-e-box</v-icon><b>例の表示</b></h4>
      <p>
        パラメータの入力例を一覧します．クリックすることでそのパラメータがセットされます．
      </p>
      <h4 class="mb-2"><v-icon class="mr-3">mdi-order-alphabetical-ascending</v-icon><b>変数の管理</b></h4>
      <p>
        変数の定義・確認・更新・削除ができます．ここで定義された変数は，パラメータの入力フォーム内で使うことが出来ます．
        例えば<code>h = Hello</code>と変数が定義されている場合，入力フォームに<code>${h} World!</code>と入力すると，パラメータとして<code>Hello World!</code>が送信されます．
      </p>
      <h4 class="mb-2"><v-icon class="mr-3">mdi-play</v-icon><b>APIリクエストの送信</b></h4>
      <p>
        セットされているパラメータが指定されたWebAPIに送信されます．
      </p>
  </div>
</template>
