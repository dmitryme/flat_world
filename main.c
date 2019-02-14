#include "c/proto_builder.h"
#include "c/proto_json_printer.h"
#include <stdio.h>
#include <assert.h>

int32_t main()
{
   // encode 
   flatcc_builder_t b;
   flatcc_builder_init(&b);

   proto_Order_start_as_root(&b);
   proto_Order_id_add(&b, 100);
   proto_Order_end_as_root(&b);
   size_t size = 0;
   void* buf = flatcc_builder_finalize_aligned_buffer(&b, &size);

   /*for(size_t i = 0; i < size; ++i)*/
   /*{*/
      /*printf("\\x%02x", ((unsigned char*)buf)[i]);*/
   /*}*/
   /*printf("\n");*/

   {
      // decode self
      proto_Order_table_t t = proto_Order_as_root(buf);
      printf("%d\n", proto_Order_id_get(t));
   }

   {
      // print self
      flatcc_json_printer_t ctx;
      char json[4096] = {};
      flatcc_json_printer_init_buffer(&ctx, json, sizeof(json));
      proto_print_json(&ctx, buf, size);
      printf("%s\n", json);
   }

   {
      // decode python encoded Order
      const char buf[] = {0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x08, 0x00, 0x04, 0x00, 0x06, 0x00, 0x00, 0x00, 0x64, 0x00, 0x00, 0x00};
      proto_Order_table_t t = proto_Order_as_root(buf);
      assert(t);
      printf("%d\n", proto_Order_id_get(t));
   }

   return 0;
}
