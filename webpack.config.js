const path = require('path');
const webpack = require('webpack');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const { name } = require('./package.json');

module.exports = {
  entry: './output/Main.js',
  output: {
    filename: 'bundle.js',
    path: path.resolve(__dirname, 'example/temp')
  },
  resolve: {
    modules: [path.join(__dirname, './node_modules')],
    moduleExtensions: ['js']
  },
  mode: 'development',
  plugins: [
    new webpack.NamedModulesPlugin(),
    new webpack.HotModuleReplacementPlugin(),
    new HtmlWebpackPlugin({
      template: path.resolve(__dirname, 'example/index.html'),
      inject: true
    })
  ],
  devtool: 'eval',
  devServer: {
    contentBase: './example',
    hot: true,
    watchOptions: {
      aggregateTimeout: 2000,
      poll: 1000
    }
  },
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
