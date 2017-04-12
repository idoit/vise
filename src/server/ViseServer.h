/** @file   vise_server.h
 *  @brief  provides HTTP based user interface for VISE
 *
 *  Provides a HTTP based user interface to configure, train and query the
 *  VGG Image Search Enginer (VISE)
 *
 *  @author Abhishek Dutta (adutta@robots.ox.ac.uk)
 *  @date   31 March 2017
 */

#ifndef _VISE_SERVER_H
#define _VISE_SERVER_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <unistd.h>
#include <stdexcept>

#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include "SearchEngine.h"

using boost::asio::ip::tcp;

class ViseServer {
 public:
  ViseServer( std::string vise_datadir );

  void Start(unsigned int port);
  bool Stop();
  bool Restart();

 private:
  unsigned int port_;
  std::string hostname_;
  std::string url_prefix_;

  boost::filesystem::path  vise_datadir_;
  boost::filesystem::path  vise_enginedir_;
  boost::filesystem::path  vise_htmldir_;
  SearchEngine search_engine_;

  // html templates
  boost::filesystem::path html_dir_;
  boost::filesystem::path vise_main_html_fn_;

  std::string html_vise_main_;
  std::vector<std::string> state_html_list_;

  boost::system::error_code error_;

  void Read();
  void Evaluate();
  void Print();
  void CloseConnection();
  void MoveToNextState();

  void HandleConnection(boost::shared_ptr<tcp::socket> p_socket);
  void HandleGetRequest(std::string resource, boost::shared_ptr<tcp::socket> p_socket);
  void HandlePostRequest(std::string resource, std::string post_data, boost::shared_ptr<tcp::socket> p_socket);

  void SendHttpResponse(std::string html, boost::shared_ptr<tcp::socket> p_socket);
  void SendHttpNotFound(boost::shared_ptr<tcp::socket> p_socket);
  void SendHttpRedirect(std::string redirect_uri, boost::shared_ptr<tcp::socket> p_socket);
  void SendErrorResponse(std::string message, std::string backtrace, boost::shared_ptr<tcp::socket> p_socket);
  void SendRawResponse(std::string response, boost::shared_ptr<tcp::socket> p_socket);
  void SendJsonResponse(std::string json, boost::shared_ptr<tcp::socket> p_socket);

  void ExtractHttpResource(std::string http_request, std::string &http_resource);
  void ExtractHttpContent(std::string http_request, std::string &http_content);

  int LoadStateHtml(unsigned int state_id, std::string &state_html);
  int LoadFile(std::string filename, std::string &file_contents);
  void WriteFile(std::string filename, std::string &file_contents);

  void SplitString(std::string s, char sep, std::vector<std::string> &tokens);
  bool ReplaceString(std::string &s, std::string old_str, std::string new_str);
};

#endif /* _VISE_SERVER_H */
