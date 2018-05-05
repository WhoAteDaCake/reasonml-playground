const path = require('path');
const webpack = require('webpack');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const { name } = require('./package.json');

module.exports = {
  // entry: './example/index.js',
  entry: './output/Main.js',
  output: {
    filename: 'bundle.js',
    path: path.resolve(__dirname, 'example/temp')
  },
  devtool: 'eval',
  devServer: {
    contentBase: './example',
    hot: true,
    noInfo: true
  },
  resolve: {
    modules: ['node_modules']
  },
  // resolve: {
  //   alias: {
  //     [name]: path.resolve(__dirname, './temp/' + name + '.js')
  //   }
  // },
  plugins: [
    new webpack.NamedModulesPlugin(),
    new webpack.HotModuleReplacementPlugin(),
    new HtmlWebpackPlugin({
      template: path.resolve(__dirname, 'example/index.html'),
      inject: true
    })
  ],
  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: /(node_modules)/,
        use: {
          loader: 'babel-loader',
          options: {
            presets: [['env', { modules: false }], 'react']
          }
        }
      },
      {
        test: /\.css$/,
        use: ['style-loader', 'css-loader']
      }
    ]
  }
};
