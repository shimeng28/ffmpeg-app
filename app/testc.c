//
//  testc.c
//  app
//
//  Created by shimeng on 2020/7/18.
//  Copyright © 2020 shimeng. All rights reserved.
//

#include "testc.h"


void rec_audio() {
  int ret = 0;
  char errors[1024];
  // 上下文
  AVFormatContext* format_ctx = NULL;
  AVDictionary* options = NULL;
  av_log_set_level(AV_LOG_DEBUG);
  
  // [[video device]:[audio device]]
  char* device_name = ":0";
  //  注册所有设备
  avdevice_register_all();
  
  // 获取格式
  AVInputFormat* iformat = av_find_input_format("avfoundation");
  ret = avformat_open_input(&format_ctx, device_name, iformat,  &options);

  if (ret < 0) {
    av_strerror(ret, errors, 1024);
    fprintf(stderr, "Fail to open audio device, [%d]%s\n", ret, errors);
    return;
  }

  int count = 0;
  AVPacket pkt;
  av_init_packet(&pkt);
  
  const char* out = "/Users/mengshi/Documents/project/ffmpeg-project/demo/app/app/audio.pcm";
  FILE* outfile = fopen(out, "wb+");

  while (1) {
    ret = av_read_frame(format_ctx, &pkt);
    if (ret == -35) {
      usleep(20);
//      av_log(NULL, AV_LOG_INFO, "ret = %d\n", ret);
      av_packet_unref(&pkt);
      continue;
    }
    if (ret != 0 || count > 500) {
      av_log(NULL, AV_LOG_INFO, "finish");
      av_packet_unref(&pkt);
      break;
    }
    count++;
    av_log(NULL, AV_LOG_INFO, "pkt size is %d count=%d \n", pkt.size, count);
    fwrite(pkt.data, pkt.size, 1, outfile);
    fflush(outfile);
    av_packet_unref(&pkt);
  }
  
  fclose(outfile);

  avformat_close_input(&format_ctx);
};
