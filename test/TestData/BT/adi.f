c---------------------------------------------------------------------
c---------------------------------------------------------------------

      subroutine  adi

c---------------------------------------------------------------------
c---------------------------------------------------------------------

      call copy_faces

c      write (*,*) "   Calling x_solve"
      call x_solve

c      write (*,*) "   Calling y_solve"
      call y_solve

c      write (*,*) "   Calling z_solve"
      call z_solve
c      write (*,*) "   After Calling z_solve"

      call add

      return
      end

