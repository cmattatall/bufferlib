import os
import shutil


if __name__ == "__main__":
    build_dir = "build"
    current_dir = os.getcwd()
    if os.path.exists(build_dir):
        shutil.rmtree(build_dir)
    os.system("cmake -S . -B %s -DBUILD_TESTING=ON" % (build_dir))
    os.system("cmake --build %s" % (build_dir))
    os.chdir("%s" % (build_dir))
    os.system("ctest -V")
    os.chdir(current_dir)

    # now redo it all but for -DBUILD_THREAD_SAFE
    if os.path.exists(build_dir):
        shutil.rmtree(build_dir)
    os.system("cmake -S . -B %s -DBUILD_TESTING=ON -DBUILD_THREAD_SAFE=ON" % (build_dir))
    os.system("cmake --build %s" % (build_dir))
    os.chdir("%s" % (build_dir))
    os.system("ctest -V")
    os.chdir(current_dir)

