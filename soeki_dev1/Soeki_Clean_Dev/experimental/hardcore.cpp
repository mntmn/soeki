/*
	Hardcore... Extract a video file to single raw frames.
	©1999 Lukas Hartmann / Atomatrix
*/




void BuildMediaFormat(int32 width, int32 height, color_space cspace, media_format *format)
{ 
      media_raw_video_format *rvf = &format->u.raw_video; 
   
      memset(format, 0, sizeof(*format)); 
   
      format->type = B_MEDIA_RAW_VIDEO; 
      rvf->last_active = (uint32)(height - 1); 
      rvf->orientation = B_VIDEO_TOP_LEFT_RIGHT; 
      rvf->pixel_width_aspect = 1; 
      rvf->pixel_height_aspect = 3; 
      rvf->display.format = cspace; 
      rvf->display.line_width = (int32)width; 
      rvf->display.line_count = (int32)height; 
      if (cspace == B_RGB32) 
         rvf->display.bytes_per_row = 4 * width; 
      else { 
         printf("can't build the format!\n"); 
         exit(5); 
      } 
}

void transcode(BMediaTrack *vidtrack,char *output, char *family_name, char *video_name)
{ 
      char *chunk; 
      char *bitmap = NULL; 
      bool found_video_encoder = false; 
      bool found_family;
      int32 i, sz, cookie; 
      int64 numFrames, j; 
      int64 framesize; 
      status_t err; 
      entry_ref ref; 
      media_format format, outfmt; 
      media_codec_info mci; 
      media_file_format mfi; 
      media_header mh; 
   
      err = get_ref_for_path(output, &ref); 
      if (err) { 
         printf("problem with get_ref_for_path() -- %s\n", strerror(err)); 
         return; 
      }

	  cookie = 0; 
      while((err = get_next_file_format(&cookie, &mfi)) == B_OK) { 
         if (strcmp(mfi.short_name, family_name) == 0) 
            break; 
      } 
   
      if (err != B_OK) { 
         printf("failed to find a file format handler !\\n"); 
         return; 
      }

	  if (vidtrack) { 
         vidtrack->EncodedFormat(&format); 
         
         if (video_name) { 
            int width, height; 
            width = format.u.encoded_video.output.display.line_width; 
            height = format.u.encoded_video.output.display.line_count; 
      
            memset(&format, 0, sizeof(format)); 
            BuildMediaFormat(width, height, B_RGB32, &format); 
            vidtrack->DecodedFormat(&format); 
            
            bitmap = (char *)malloc(width * height * 4); 
      
            cookie = 0; 
            while (get_next_encoder(&cookie, &mfi, &format, &outfmt, &mci) == B_OK) { 
               printf("found encoder %s (%d)\\n", mci.pretty_name, mci.id); 
               if (strcmp(video_name, mci.short_name) == 0) { 
                  found_video_encoder = true; 
                  break; 
               } 
			}      
         }
      }

		if (vidtrack) { 
         int is_key_frame = 0; 
            
         if (found_video_encoder) { 
            numFrames = vidtrack->CountFrames(); 
            for(j = 0; j < numFrames; j++) { 
               int64 framecount = 1; 
               printf("                                \\r"); 
               printf("processing frame: %5Ld", j); 
               fflush(stdout); 
               err = vidtrack->ReadFrames(bitmap, &framecount, &mh); 
               if (err) { 
                  printf("video: GetNextChunk error -- %s\\n", strerror(err)); 
                  break; 
               } 
               
            }
		 }
		}
};