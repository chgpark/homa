import os

class CheckFileList:
    def get_folder_path(self, folder_path):
        self.folder_path = folder_path
        self.folder_list = os.listdir(self.folder_path)
        for folder_name in self.folder_list:
            dir_path = os.path.join(self.folder_path, folder_name)
            tmp_class_list = os.listdir(dir_path)
            print('Folder name: ' + folder_name)
            for class_name in tmp_class_list:
                number_of_file = len(os.listdir(os.path.join(dir_path, class_name)))
                print(class_name + ': ' + str(number_of_file))


if __name__ == '__main__':
    cfl = CheckFileList()
    cfl.get_folder_path('/run/user/1020/gvfs/dav:host=192.168.0.3,port=5005,ssl=false,user=cpark/ResearchServer/dataset/AVTDC/cropped/classification')
